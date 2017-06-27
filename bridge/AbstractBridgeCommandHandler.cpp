#include "AbstractBridgeCommandHandler.h"

void SIMUCOPTER::AbstractBridgeCommandHandler::init() {
    m_socket_cmdIn.connect(ZMQ_BRIDGE_CMD_DISPATCH_URL.c_str());
    m_socket_cmdIn.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    m_initialized = true;
}

bool SIMUCOPTER::AbstractBridgeCommandHandler::handle_next() {
    assert(is_initialized());
    bool handled;
    char buffer[1024];
    size_t pkt_sz = m_socket_cmdIn.recv(buffer, 1024, ZMQ_NOBLOCK);
    if ((handled = pkt_sz > 0)) {
        const BridgeMessage cmd = m_serializer.deserialize(buffer, pkt_sz);
        handle(cmd);
    }

    return handled;
}
