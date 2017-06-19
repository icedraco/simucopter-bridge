//
// simucopter.h variant for the ArduCopter side
//

#pragma once

#include <thread>
#include "ArduCopterRequestHandler.h"

namespace SIMUCOPTER {
    BridgeService            simucopter_bridge_service("tcp://127.0.0.1:5555", "tcp://127.0.0.1:5556");
    ArduCopterRequestHandler simucopter_request_handler;

    void request_thread(BridgeService& service);
    void init_simucopter(void);
}
