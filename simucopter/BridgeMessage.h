//
// Created by icedragon on 6/8/17.
//

#pragma once

#include <string.h>
#include <cstdint>

namespace SIMUCOPTER {
    const int BRIDGE_MSG_DATA_CAPACITY = 64;

    class BridgeMessage {
    public:
        const int id;

        BridgeMessage(int msgid) : id(msgid), data_sz(0) {};

        /**
         * NOTE: This is not the size of the entire message!
         * @return size of the message data in bytes
         */
        inline size_t size(void) const { return data_sz; }

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
        size_t get_data(void* dst, size_t maxlen) const;

    private:
        size_t data_sz;
        char data[BRIDGE_MSG_DATA_CAPACITY];
    };
}
