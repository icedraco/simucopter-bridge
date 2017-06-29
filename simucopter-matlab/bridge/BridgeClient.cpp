#include "BridgeClient.h"

void SIMUCOPTER::BridgeClient::init(void) {
    if (!is_initialized()) {
        m_socket_requests.connect(m_reqAddrUrl.c_str());
        m_socket_cmdPublish.connect(m_cmdAddrUrl.c_str());
        m_initialized = true;
    }
}

void SIMUCOPTER::BridgeClient::close(void) {
    if (is_initialized()) {
        m_socket_requests.close();
        m_socket_cmdPublish.close();
        m_initialized = false;
    }
}

double SIMUCOPTER::BridgeClient::request_double(int msgid) {
    assert(is_initialized());
    double result;
    BridgeMessage response = request(msgid);
    response.load_data(&result, sizeof(result));
    return result;
}

int SIMUCOPTER::BridgeClient::request_int(int msgid) {
    assert(is_initialized());
    int result;
    BridgeMessage response = request(msgid);
    response.load_data(&result, sizeof(result));
    return result;
}

bool SIMUCOPTER::BridgeClient::send_command(int msgid) {
    assert(is_initialized());
    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    char buffer[1024];
    size_t pkt_sz = m_serializer.serialize(cmd, buffer, 1024);
    return m_socket_cmdPublish.send(buffer, pkt_sz, ZMQ_NOBLOCK) > 0;
}

bool SIMUCOPTER::BridgeClient::send_command(int msgid, double arg1) {
    assert(is_initialized());
    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    cmd.set_data(&arg1, sizeof(arg1));
    char buffer[1024];
    size_t pkt_sz = m_serializer.serialize(cmd, buffer, 1024);
    return m_socket_cmdPublish.send(buffer, pkt_sz, ZMQ_NOBLOCK) > 0;
}

bool SIMUCOPTER::BridgeClient::send_command(int msgid, double arg1, double arg2) {
    assert(is_initialized());
    struct {
        double arg1;
        double arg2;
    } s_args;

    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    s_args.arg1 = arg1;
    s_args.arg2 = arg2;

    cmd.set_data(&s_args, sizeof(s_args));
    char buffer[1024];
    size_t pkt_sz = m_serializer.serialize(cmd, buffer, 1024);
    return m_socket_cmdPublish.send(buffer, pkt_sz, ZMQ_NOBLOCK) > 0;
}


/*** PRIVATE *****************************************************************/

BridgeMessage SIMUCOPTER::BridgeClient::request(int msgid) {
    assert(is_initialized());
    char buffer[1024];
    size_t pkt_sz;

    BridgeMessage req_msg(BridgeMessageType::REQUEST, msgid);
    pkt_sz = m_serializer.serialize(req_msg, buffer, 1024);
    m_socket_requests.send(buffer, pkt_sz, ZMQ_NOBLOCK);

    pkt_sz = m_socket_requests.recv(buffer, 1024);
    assert(pkt_sz > 0);

    BridgeMessage response = m_serializer.deserialize(buffer, 1024);
    assert(response.type == BridgeMessageType::REPLY);
    assert(response.id == msgid);
    return response;
}
