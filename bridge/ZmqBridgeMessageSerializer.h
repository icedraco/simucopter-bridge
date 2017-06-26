#pragma  once

#include <zmq.hpp>
#include "BridgeMessage.h"

using SIMUCOPTER::BridgeMessage;

namespace SIMUCOPTER {
    /**
     * Responsible for serializing and de-serializing a BridgeMessage object
     * into a ZeroMQ messages.
     */
    class ZmqBridgeMessageSerializer {
    public:
        size_t serialize(const BridgeMessage& msg, void* dst, size_t dst_sz) const;
        BridgeMessage deserialize(const void* src, size_t len) const;
    };
}
