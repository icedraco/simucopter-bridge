#pragma once

#include <string>
#include <zmq.hpp>

namespace SIMUCOPTER {
    static const std::string ZMQ_BRIDGE_REQ_URL = "tcp://127.0.0.1:5555";
    static const std::string ZMQ_BRIDGE_CMD_URL = "tcp://127.0.0.1:5556";
    static const std::string ZMQ_SITL_REQ_URL = "tcp://127.0.0.1:5565";
    static const std::string ZMQ_SITL_CMD_URL = "tcp://127.0.0.1:5566";
    static const std::string ZMQ_BRIDGE_CMD_DISPATCH_URL = "inproc://simulink_commands";
    static const std::string ZMQ_SITL_CMD_DISPATCH_URL = "inproc://sitl_commands";

    static const int ZMQ_CMD_PUBLISH_TIMEOUT_MSEC = 500;
    static const int ZMQ_CMD_DISPATCH_TIMEOUT_MSEC = 500;
    static const int ZMQ_NUM_THREADS = 1;
    static const int MAX_MSG_PER_CYCLE = 5;  // messages per update() cycle

    const int BRIDGE_MSG_DATA_CAPACITY = 64;  // bytes

    enum BridgeMessageType { REQUEST=1, COMMAND=2, REPLY=3};

    class ZmqContextContainer {
    public:
        static zmq::context_t& get_context() {
            static zmq::context_t* context = nullptr;
            if (context == nullptr) {
                context = new zmq::context_t(ZMQ_NUM_THREADS);
            }
            return *context;
        }
    };

}