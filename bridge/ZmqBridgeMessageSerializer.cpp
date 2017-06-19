//
// Created by icedragon on 6/18/17.
//

#include "ZmqBridgeMessageSerializer.h"

struct s_bridge_msg {
    int type;
    int id;
    size_t data_sz;
    char data[SIMUCOPTER::BRIDGE_MSG_DATA_CAPACITY];
};


zmq::message_t SIMUCOPTER::ZmqBridgeMessageSerializer::serialize(const BridgeMessage& msg) const {
    s_bridge_msg msg_struct;
    msg_struct.type = msg.type;
    msg_struct.id = msg.id;
    msg_struct.data_sz = msg.size();
    msg.load_data(msg_struct.data, sizeof(msg_struct.data));

    zmq::message_t zmq_msg(sizeof(msg_struct));
    memcpy(zmq_msg.data(), &msg_struct, sizeof(msg_struct));
    return zmq_msg;
}

BridgeMessage SIMUCOPTER::ZmqBridgeMessageSerializer::deserialize(const zmq::message_t& msg) const {
    s_bridge_msg *msg_struct = (s_bridge_msg*)msg.data();
    BridgeMessage bridge_msg((SIMUCOPTER::BridgeMessageType)msg_struct->type, msg_struct->id);
    bridge_msg.set_data(msg_struct->data, msg_struct->data_sz);
    return bridge_msg;
}
