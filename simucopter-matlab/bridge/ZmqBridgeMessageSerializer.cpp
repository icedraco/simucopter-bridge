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


size_t SIMUCOPTER::ZmqBridgeMessageSerializer::serialize(const BridgeMessage& msg, void* dst, size_t dst_sz) const {
    assert(dst_sz >= sizeof(struct s_bridge_msg) + SIMUCOPTER::BRIDGE_MSG_DATA_CAPACITY);
    s_bridge_msg* msg_struct = (s_bridge_msg*)dst;
    msg_struct->type = msg.type;
    msg_struct->id = msg.id;
    msg_struct->data_sz = msg.size();
    size_t data_len = msg.load_data(msg_struct->data, SIMUCOPTER::BRIDGE_MSG_DATA_CAPACITY);
    size_t actual_size = sizeof(struct s_bridge_msg) - sizeof(char*) + data_len;
    return actual_size;
}

BridgeMessage SIMUCOPTER::ZmqBridgeMessageSerializer::deserialize(const void* msg, size_t len) const {
    const s_bridge_msg* msg_struct = (s_bridge_msg*)msg;
    assert(len >= sizeof(struct s_bridge_msg) - sizeof(char*));

    BridgeMessage bridge_msg((SIMUCOPTER::BridgeMessageType)msg_struct->type, msg_struct->id);
    bridge_msg.set_data(msg_struct->data, msg_struct->data_sz);
    return bridge_msg;
}
