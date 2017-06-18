#include "AbstractBridgeCommandHandler.h"

void SIMUCOPTER::AbstractBridgeCommandHandler::init() {
    // socket options
    // none

    // connect
    m_socket_cmdPub.connect(ZMQ_BRIDGE_CMD_DISPATCH_URL);

    // set initialized flag
    m_initialized = true;
}

bool SIMUCOPTER::AbstractBridgeCommandHandler::handle_next() {
    assert(is_initialized());
    zmq::message_t msg;
    bool result = m_socket_cmdPub.recv(&msg, ZMQ_NOBLOCK);
    if (result) {
        const BridgeMessage cmd = m_serializer.deserialize(msg);
        handle(cmd);
    }

    return result;
}
