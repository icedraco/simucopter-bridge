#include "AbstractBridgeCommandHandler.h"

void SIMUCOPTER::AbstractBridgeCommandHandler::init() {
    m_socket_cmdIn.connect(ZMQ_BRIDGE_CMD_DISPATCH_URL);
    m_socket_cmdIn.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    m_initialized = true;
}

bool SIMUCOPTER::AbstractBridgeCommandHandler::handle_next() {
    assert(is_initialized());
    zmq::message_t msg;
    bool result = m_socket_cmdIn.recv(&msg, ZMQ_NOBLOCK);
    if (result) {
        const BridgeMessage cmd = m_serializer.deserialize(msg);
        handle(cmd);
    }

    return result;
}
