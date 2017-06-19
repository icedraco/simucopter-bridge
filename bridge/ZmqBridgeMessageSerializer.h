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
        zmq::message_t serialize(const BridgeMessage& msg) const;
        BridgeMessage deserialize(const zmq::message_t& msg) const;
    };
}
