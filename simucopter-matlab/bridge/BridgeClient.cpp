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
    char buffer[BRIDGE_MSG_DATA_CAPACITY];
    double result;
    BridgeMessage response = request(msgid);
    response.load_data(&buffer, BRIDGE_MSG_DATA_CAPACITY);
    m_packer.unpack(buffer, BRIDGE_MSG_DATA_CAPACITY, &result);
    return result;
}

int SIMUCOPTER::BridgeClient::request_int(int msgid) {
    assert(is_initialized());
    char buffer[BRIDGE_MSG_DATA_CAPACITY];
    int result;
    BridgeMessage response = request(msgid);
    response.load_data(&buffer, BRIDGE_MSG_DATA_CAPACITY);
    m_packer.unpack(buffer, BRIDGE_MSG_DATA_CAPACITY, &result);
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

    // pack arguments into the buffer
    char buffer_args[BRIDGE_MSG_DATA_CAPACITY];
    size_t packed_sz = m_packer.pack(buffer_args, BRIDGE_MSG_DATA_CAPACITY, arg1, arg2);
    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    cmd.set_data(&buffer_args, packed_sz);

    char buffer_msg[1024];
    size_t pkt_sz = m_serializer.serialize(cmd, buffer_msg, 1024);
    return m_socket_cmdPublish.send(buffer_msg, pkt_sz, ZMQ_NOBLOCK) > 0;
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
