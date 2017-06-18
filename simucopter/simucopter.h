#pragma once

#include <string>

namespace SIMUCOPTER {
    static const std::string ZMQ_BRIDGE_REQ_URL = "tcp://127.0.0.1:5555";
    static const std::string ZMQ_BRIDGE_CMD_URL = "tcp://127.0.0.1:5556";
    static const std::string ZMQ_BRIDGE_CMD_DISPATCH_URL = "inproc://simulink_commands";

    static const int ZMQ_REP_RCV_TIMEOUT_MSEC = 10;
    static const int ZMQ_NUM_THREADS = 1;
    static const int MAX_MSG_PER_CYCLE = 5;  // messages per update() cycle

    const int BRIDGE_MSG_DATA_CAPACITY = 64;  // bytes

    enum BridgeMessageType { REQUEST=1, COMMAND=2, REPLY=3};

}