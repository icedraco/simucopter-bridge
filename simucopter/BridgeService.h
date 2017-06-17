#pragma once

#include <map>
#include <deque>
#include <zmq.hpp>

#include "BridgeRequestHandler.h"


namespace SIMUCOPTER {
    static const int ZMQ_REP_RCV_TIMEOUT_MSEC = 10;
    static const int ZMQ_NUM_THREADS = 1;
    static const int MAX_MSG_PER_CYCLE = 5;  // messages per update() cycle

    static const std::string ZMQ_BRIDGE_REQ_URL = "tcp://127.0.0.1:5555";
    static const std::string ZMQ_BRIDGE_CMD_URL = "tcp://127.0.0.1:5556";
    static const std::string ZMQ_BRIDGE_CMD_DISPATCH_URL = "inproc://simulink_commands";

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
         */
        BridgeService(
                const std::string req_url = ZMQ_BRIDGE_REQ_URL,
                const std::string cmd_url = ZMQ_BRIDGE_CMD_URL) :
                m_reqAddrUrl(req_url), m_cmdAddrUrl(cmd_url),
                m_context(ZMQ_NUM_THREADS),
                m_socket_requestHandler(m_context, ZMQ_REP),
                m_socket_cmdReceiver(m_context, ZMQ_PAIR),
                m_socket_cmdDispatcher(m_context, ZMQ_PUB) {}

        /**
         * @return true if this component was initialized; false otherwise
         */
        inline bool is_initialized() const { return m_initialized; }

        /**
         * Initialize this service (must be executed after instantiation)
         */
        void init(void);

        /**
         * Handle new incoming messages from the sockets
         */
        void update(void);

        /**
         * Get a request handler for the given message ID, if assigned
         *
         * @param msgid message ID
         * @return pointer to a BridgeRequestHandler instance, or nullptr if not assigned
         */
        BridgeRequestHandler* handler(int msgid);

        /**
         * Assign a BridgeRequestHandler instance to handle incoming commands
         * of the specified message ID.
         *
         * @param msgid message ID
         * @param handler handler responsible for handling messages
         */
        inline void set_request_handler(int msgid, BridgeRequestHandler* handler) {
            assert(handler != nullptr);
            m_handlers[msgid] = handler;
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

        bool m_initialized = false;
        std::map<int, BridgeRequestHandler*> m_handlers;

        // ZMQ context
        zmq::context_t m_context;

        // for blocking data requests from Simulink
        zmq::socket_t m_socket_requestHandler;

        // receives commands from Simulink
        zmq::socket_t m_socket_cmdReceiver;

        // publishes commands to Flight Mode Code
        zmq::socket_t m_socket_cmdDispatcher;
    };
}
