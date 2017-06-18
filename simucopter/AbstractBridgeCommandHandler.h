#pragma once

#include <zmq.hpp>
#include "simucopter.h"
#include "BridgeMessage.h"
#include "ZmqBridgeMessageSerializer.h"

namespace SIMUCOPTER {

    /**
     * This is an abstract class for a BridgeCommandHandler
     *
     * A command handler normally runs as a part of an ArduPilot flight mode
     * and polls for incoming command messages when it can using handle_next()
     * method.
     *
     * An implementing subclass must put its command handling logic into the
     * handle() method, and run handle_next() whenever a message can/should
     * be handled if available.
     */
    class AbstractBridgeCommandHandler {
    public:
        AbstractBridgeCommandHandler() :
                m_serializer(),
                m_context(ZMQ_NUM_THREADS),
                m_socket_cmdPub(m_context, ZMQ_SUB) {}

        /**
         * @return true if this component was initialized; false otherwise
         */
        inline bool is_initialized(void) const { return m_initialized; }

        /**
         * Initialize this handler (must be executed after instantiation)
         */
        void init(void);

        /**
         * Handle next message (if available)
         *
         * This method launches the abstract handle() method with the retrieved
         * message as an argument. The system is to handle that message.
         *
         * @return false if no message was received this cycle
         */
        bool handle_next(void);

        /**
         * Handle an incoming command message
         * @param cmd command message
         */
        virtual void handle(const BridgeMessage& cmd) = 0;

    private:
        const ZmqBridgeMessageSerializer m_serializer;
        bool m_initialized = false;
        zmq::context_t m_context;
        zmq::socket_t m_socket_cmdPub;
    };

}
