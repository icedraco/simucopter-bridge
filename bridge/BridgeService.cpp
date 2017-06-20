#include "BridgeService.h"

void SIMUCOPTER::BridgeService::init(void) {
    if (!is_initialized()) {
        m_socket_cmdReceiver.bind(m_cmdAddrUrl);
        m_socket_requestHandler.bind(m_reqAddrUrl);
        m_socket_cmdOut.bind(ZMQ_BRIDGE_CMD_DISPATCH_URL);
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

    // handle incoming requests from Simulink getter blocks
    // these blocks will stop the agent until they get a response, so they must
    // be served ASAP - we do it here through AbstractBridgeRequestHandler map
    flag_depleted = false;
    for (int i = 0; !flag_depleted && i < MAX_MSG_PER_CYCLE; i++) {
        zmq::message_t req_msg;
        if (m_socket_requestHandler.recv(&req_msg, ZMQ_NOBLOCK)) {
            BridgeMessage request = m_serializer.deserialize(req_msg);
            assert(request.type == BridgeMessageType::REQUEST);

            BridgeMessage response = request.get_reply();
            handler(request.id).handle(request, response);
            zmq::message_t zmq_rep_msg = m_serializer.serialize(response);
            m_socket_requestHandler.send(&zmq_rep_msg, ZMQ_NOBLOCK);
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
        zmq::message_t cmd_msg;
        if (m_socket_cmdReceiver.recv(&cmd_msg, ZMQ_NOBLOCK)) {
            m_socket_cmdOut.send(&cmd_msg, ZMQ_NOBLOCK);
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
