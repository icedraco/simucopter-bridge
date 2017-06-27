#pragma once

#include <map>
#include <deque>
#include <zmq.hpp>

#include "simucopter-bridge.h"
#include "AbstractBridgeRequestHandler.h"
#include "ZmqBridgeMessageSerializer.h"


namespace SIMUCOPTER {
    class ZeroRequestHandler: public AbstractBridgeRequestHandler {
    public:
        virtual ~ZeroRequestHandler() {}
        void handle(const BridgeMessage& request, BridgeMessage& response) {
            int zero = 0;
            response.set_data(&zero, sizeof(zero));
        }
    };

    /**
     * This class is responsible for sitting on the server side (ArduPilot),
     * and handling various requests from BridgeClient, as well as ArduPilot
     * itself (command dispatching purposes)
     */
    class BridgeService {
    public:
        /**
         * Class Constructor
         *
         * Example ZMQ URL: "tcp://127.0.0.1:5555"
         *
         * @param req_url ZMQ URL for listening to requests
         * @param cmd_url ZMQ URL for listening to commands
         * @param dispatch_url ZMQ URL for dispatching commands to flight mode
         */
        BridgeService(
                const std::string req_url = ZMQ_BRIDGE_REQ_URL,
                const std::string cmd_url = ZMQ_BRIDGE_CMD_URL,
                const std::string dispatch_url = ZMQ_BRIDGE_CMD_DISPATCH_URL) :
                m_reqAddrUrl(req_url),
                m_cmdAddrUrl(cmd_url),
                m_dispatchAddrUrl(dispatch_url),
                m_serializer(),
                m_defaultHandler(new ZeroRequestHandler()),
                m_context(ZmqContextContainer::get_context()),
                m_socket_requestHandler(m_context, ZMQ_REP),
                m_socket_cmdReceiver(m_context, ZMQ_SUB),
                m_socket_cmdOut(m_context, ZMQ_PUB)
        {
            printf("DEBUG: BridgeService(%s, %s)\n", req_url.c_str(), cmd_url.c_str());
            m_socket_cmdReceiver.setsockopt(ZMQ_SUBSCRIBE, "", 0);
            m_socket_cmdReceiver.setsockopt(ZMQ_RCVTIMEO, &ZMQ_CMD_PUBLISH_TIMEOUT_MSEC, sizeof(ZMQ_CMD_PUBLISH_TIMEOUT_MSEC));
            m_socket_cmdOut.setsockopt(ZMQ_SNDTIMEO, &ZMQ_CMD_DISPATCH_TIMEOUT_MSEC, sizeof(ZMQ_CMD_DISPATCH_TIMEOUT_MSEC));
        }

        virtual ~BridgeService() {
            if (is_initialized())
                close();

            delete m_defaultHandler;
        }

        /**
         * @return true if this component was initialized; false otherwise
         */
        inline bool is_initialized() const { return m_initialized; }

        /**
         * @return request handler used by default if none assigned
         */
        inline AbstractBridgeRequestHandler* default_handler() const { return m_defaultHandler; }

        /**
         * Initialize this service (must be executed after instantiation)
         */
        void init(void);

        /**
         * Terminate the service and close all its connections
         */
        void close(void);

        /**
         * Handle new incoming messages from the sockets
         * @return true if new events were handled; false if nothing new this cycle
         */
        bool update(void);

        /**
         * Get a request handler for the given message ID, if assigned
         *
         * @param msgid message ID
         * @return pointer to a BridgeRequestHandler instance, or default handler if not assigned
         */
        AbstractBridgeRequestHandler& handler(int msgid);

        /**
         * Assign a BridgeRequestHandler instance to handle incoming commands
         * of the specified message ID.
         *
         * @param msgid message ID
         * @param new_handler handler responsible for handling messages
         */
        inline void set_request_handler(int msgid, AbstractBridgeRequestHandler* new_handler) {
            assert(new_handler != nullptr);
            m_handlers[msgid] = new_handler;
        }

        /**
         * Clear/remove whatever handler is currently responsible for the given
         * message ID.
         *
         * @param msgid message ID
         */
        inline void clear_request_handler(int msgid) { m_handlers.erase(msgid); }


    private:
        const std::string m_reqAddrUrl; // listening address for request handler
        const std::string m_cmdAddrUrl; // listening address for command dispatcher
        const std::string m_dispatchAddrUrl; // publishing address for command dispatcher

        const ZmqBridgeMessageSerializer m_serializer;

        bool m_initialized = false;
        AbstractBridgeRequestHandler* m_defaultHandler;
        std::map<int, AbstractBridgeRequestHandler*> m_handlers;

        // ZMQ context
        zmq::context_t& m_context;

        // for blocking data requests from Simulink
        zmq::socket_t m_socket_requestHandler;

        // receives commands from Simulink
        zmq::socket_t m_socket_cmdReceiver;

        // publishes commands to Flight Mode Code
        zmq::socket_t m_socket_cmdOut;
    };
}
