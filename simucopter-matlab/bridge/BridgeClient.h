#pragma once

#include <zmq.hpp>

#include "simucopter-bridge.h"
#include "ZmqBridgeMessageSerializer.h"
#include "ArgumentPacker.h"

namespace SIMUCOPTER {

    /**
     * Connects to a BridgeService instance over a ZMQ transport
     */
    class BridgeClient {
    public:
        /**
         * Class Constructor
         *
         * Example ZMQ URL: "tcp://127.0.0.1:5555"
         *
         * @param req_addr ZMQ URL for remote request handler
         * @param cmd_addr ZMQ URL for remote command handler
         */
        BridgeClient(
                std::string req_addr = ZMQ_BRIDGE_REQ_URL,
                std::string cmd_addr = ZMQ_BRIDGE_CMD_URL) :
                m_reqAddrUrl(req_addr),
                m_cmdAddrUrl(cmd_addr),
                m_serializer(),
                m_context(ZmqContextContainer::get_context()),
                m_socket_requests(m_context, ZMQ_REQ),
                m_socket_cmdPublish(m_context, ZMQ_PUB)
        {
//            m_socket_requests.setsockopt(ZMQ_REQ_RELAXED, 1);
//            m_socket_requests.setsockopt(ZMQ_REQ_CORRELATE, 1);
            m_socket_cmdPublish.setsockopt(ZMQ_SNDTIMEO, &ZMQ_CMD_PUBLISH_TIMEOUT_MSEC, sizeof(ZMQ_CMD_PUBLISH_TIMEOUT_MSEC));
        }

        BridgeClient(BridgeClient& other) = delete;

        virtual ~BridgeClient() {
            if (is_initialized())
                close();
        }

        /**
         * @return true if this component was initialized; false otherwise
         */
        inline bool is_initialized() const { return m_initialized; }

        /**
         * Initialize this client (must be executed after instantiation)
         */
        void init(void);

        /**
         * Terminate the client and close all its connections
         */
        void close(void);

        /**
         * Send a request, expecting a DOUBLE value in return
         * @param msgid message ID
         * @return result for the given message
         */
        double request_double(int msgid);

        /**
         * Send a request, expecting an INT value in return
         * @param msgid message ID
         * @return result for the given message
         */
        int request_int(int msgid);

        /**
         * Send a command to the service with no arguments
         * @param msgid message ID
         * @return false if failed to send command
         */
        bool send_command(int msgid);

        /**
         * Send a command to the service with one DOUBLE argument
         * @param msgid message ID
         * @param arg1 argument 1
         * @return false if failed to send command
         */
        bool send_command(int msgid, double arg1);

        /**
         * Send a command to the service with two DOUBLE arguments
         * @param msgid message ID
         * @param arg1 argument 1
         * @param arg2 argument 2
         * @return false if failed to send command
         */
        bool send_command(int msgid, double arg1, double arg2);


    private:
        BridgeMessage request(int msgid);

    private:
        const std::string m_reqAddrUrl; // address for request handler
        const std::string m_cmdAddrUrl; // address for command dispatcher
        const ZmqBridgeMessageSerializer m_serializer;
        const ArgumentPacker m_packer;

        bool m_initialized = false;

        // ZMQ context
        zmq::context_t& m_context;

        // for blocking data requests from Simulink (getter blocks)
        zmq::socket_t m_socket_requests;

        // for commands from Simulink (setter blocks)
        zmq::socket_t m_socket_cmdPublish;
    };

}
