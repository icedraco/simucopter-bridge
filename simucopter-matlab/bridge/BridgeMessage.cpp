#include "BridgeMessage.h"

using namespace SIMUCOPTER;

size_t BridgeMessage::set_data(const void *src, size_t length) {
    if (length > BRIDGE_MSG_DATA_CAPACITY)
        length = BRIDGE_MSG_DATA_CAPACITY;

    memcpy(m_data, src, length);
    data_sz = length;
    return data_sz;
}

size_t BridgeMessage::load_data(void *dst, size_t maxlen) const {
    size_t len = maxlen > data_sz ? data_sz : maxlen;
    memcpy(dst, m_data, len);
    return len;
}
