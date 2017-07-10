#pragma once

#include <string.h>
#include <cstdint>

#include "simucopter-bridge.h"

namespace SIMUCOPTER {
    class BridgeMessage {
    public:
        const int id;
        const BridgeMessageType type;

        BridgeMessage(BridgeMessageType msgtype, int msgid)
                : type(msgtype), id(msgid), data_sz(0) {}

        BridgeMessage(const BridgeMessage& other) : type(other.type), id(other.id) {
            data_sz = other.load_data(m_data, BRIDGE_MSG_DATA_CAPACITY);
        }

        /**
         * NOTE: This is not the size of the entire message!
         * @return size of the message data in bytes
         */
        inline size_t size(void) const { return data_sz; }

        /**
         * @return read-only-constrained pointer to the internal data buffer
         */
        inline const void* data(void) const { return (void*)m_data; }

        /**
         * Set raw data for this message
         *
         * NOTE: If the raw data is longer than MSG_DATA_CAPACITY, it will be
         *       truncated!
         *
         * @param src source of the raw data
         * @param length length (in bytes) to copy
         * @return length that was actually copied
         */
        size_t set_data(const void* src, size_t length);

        /**
         * Copy raw data from this message into a given buffer
         *
         * NOTE: If the buffer capacity is too low, the message will be
         *       truncated!
         *
         * @param dst destination buffer
         * @param maxlen buffer capacity
         * @return length that was actually copied
         */
        size_t load_data(void *dst, size_t maxlen) const;

        /**
         * Get a "reply" message instance for this message
         *
         * The new instance would have the same message ID and REPLY as a type,
         * as well as no data.
         *
         * @return reply BridgeMessage instance for current message
         */
        inline BridgeMessage get_reply() const { return BridgeMessage(BridgeMessageType::REPLY, id); }

    private:
        size_t data_sz;
        char m_data[BRIDGE_MSG_DATA_CAPACITY];
    };
}
