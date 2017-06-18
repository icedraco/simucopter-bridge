#include "BridgeClient.h"

void SIMUCOPTER::BridgeClient::init() {
    // socket options
    m_socket_requests.setsockopt(ZMQ_REQ_RELAXED, 1);
    m_socket_requests.setsockopt(ZMQ_REQ_CORRELATE, 1);
    m_socket_cmdTransmit.setsockopt(ZMQ_SNDTIMEO, ZMQ_REP_RCV_TIMEOUT_MSEC);

    // connect
    m_socket_requests.connect(m_reqAddrUrl);
    m_socket_cmdTransmit.connect(m_cmdAddrUrl);

    // set initialized flag
    m_initialized = true;
}

double SIMUCOPTER::BridgeClient::request_double(int msgid) {
    double result;
    BridgeMessage response = request(msgid);
    response.load_data(&result, sizeof(result));
    return result;
}

int SIMUCOPTER::BridgeClient::request_int(int msgid) {
    int result;
    BridgeMessage response = request(msgid);
    response.load_data(&result, sizeof(result));
    return result;
}

void SIMUCOPTER::BridgeClient::send_command(int msgid) {
    assert(is_initialized());
    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    m_socket_cmdTransmit.send(m_serializer.serialize(cmd), ZMQ_NOBLOCK);
}

void SIMUCOPTER::BridgeClient::send_command(int msgid, double arg1) {
    assert(is_initialized());
    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    cmd.set_data(&arg1, sizeof(arg1));
    m_socket_cmdTransmit.send(m_serializer.serialize(cmd), ZMQ_NOBLOCK);
}

void SIMUCOPTER::BridgeClient::send_command(int msgid, double arg1, double arg2) {
    assert(is_initialized());
    struct {
        double arg1;
        double arg2;
    } s_args;

    BridgeMessage cmd(BridgeMessageType::COMMAND, msgid);
    s_args.arg1 = arg1;
    s_args.arg2 = arg2;

    cmd.set_data(&s_args, sizeof(s_args));
    m_socket_cmdTransmit.send(m_serializer.serialize(cmd), ZMQ_NOBLOCK);
}


/*** PRIVATE *****************************************************************/

BridgeMessage SIMUCOPTER::BridgeClient::request(int msgid) {
    assert(is_initialized());
    BridgeMessage request(BridgeMessageType::REQUEST, msgid);
    m_socket_requests.send(m_serializer.serialize(request));

    zmq::message_t msg;
    assert(m_socket_requests.recv(&msg));

    BridgeMessage response = m_serializer.deserialize(msg);
    assert(response.type == BridgeMessageType::REPLY);
    assert(response.id == request.id);

    return response;
}