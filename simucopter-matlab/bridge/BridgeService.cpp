#include "BridgeService.h"

void SIMUCOPTER::BridgeService::init(void) {
    if (!is_initialized()) {
        printf("BridgeService -> binding to: %s, %s, %s\n",
               m_cmdAddrUrl.c_str(), m_reqAddrUrl.c_str(), m_dispatchAddrUrl.c_str());

        m_socket_cmdReceiver.bind(m_cmdAddrUrl.c_str());
        m_socket_requestHandler.bind(m_reqAddrUrl.c_str());
        m_socket_cmdOut.bind(m_dispatchAddrUrl.c_str());
        m_initialized = true;
    }
}

void SIMUCOPTER::BridgeService::close(void) {
    if (is_initialized()) {
        m_socket_requestHandler.close();
        m_socket_cmdReceiver.close();
        m_socket_cmdOut.close();
        m_initialized = false;
    }
}

bool SIMUCOPTER::BridgeService::update(void) {
    assert(is_initialized());
    bool handled = false;
    bool flag_depleted;

    char buffer[1024];
    size_t msg_sz, pkt_sz;

    // handle incoming requests from Simulink getter blocks
    // these blocks will stop the agent until they get a response, so they must
    // be served ASAP - we do it here through AbstractBridgeRequestHandler map
    flag_depleted = false;
    for (int i = 0; !flag_depleted && i < MAX_MSG_PER_CYCLE; i++) {
        msg_sz = m_socket_requestHandler.recv(buffer, 1024, ZMQ_NOBLOCK);
        if (msg_sz > 0) {
            BridgeMessage request = m_serializer.deserialize(buffer, msg_sz);

            assert(request.type == BridgeMessageType::REQUEST);

            BridgeMessage response = request.get_reply();
            handler(request.id).handle(request, response);

            pkt_sz = m_serializer.serialize(response, buffer, 1024);
            m_socket_requestHandler.send(buffer, pkt_sz, ZMQ_NOBLOCK);
            handled = true;
        } else {
            flag_depleted = true;
        }
    }

    // handle incoming commands from Simulink setter blocks
    // these commands should be forwarded to the flight mode code via the dispatcher
    // socket. if the flight mode is not running, those commands will simply
    // be dropped, which is OK.
    flag_depleted = false;
    for (int i = 0; !flag_depleted && i < MAX_MSG_PER_CYCLE; i++) {
        if ((msg_sz = m_socket_cmdReceiver.recv(buffer, 1024, ZMQ_NOBLOCK)) > 0) {
            m_socket_cmdOut.send(buffer, msg_sz, ZMQ_NOBLOCK);
            handled = true;
        } else {
            flag_depleted = true;
        }
    }

    return handled;
}

SIMUCOPTER::AbstractBridgeRequestHandler& SIMUCOPTER::BridgeService::handler(int msgid) {
    auto iter = m_handlers.find(msgid);
    return iter != m_handlers.end() ? *iter->second : *default_handler();
}
