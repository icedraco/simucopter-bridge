#pragma once

//
// INTEGRATION POINT: SimuCopter<->SITL
//
// This file is included from libraries/AP_HAL_SITL/HAL_SITL_Class.cpp and is
// used to initiatlize the entire SimuCopter system along with its
// communication bridge.
//

#include <AP_HAL/AP_HAL.h>
#include <bridge/BridgeService.h>
#include <bridge/simucopter-bridge.h>
#include "SitlRequestHandler.h"

extern const AP_HAL::HAL& hal;

namespace SIMUCOPTER {

    class SimucopterSitlServer {
    public:
        SimucopterSitlServer() : sitl_bridge_service(ZMQ_SITL_REQ_URL, ZMQ_SITL_CMD_URL, ZMQ_SITL_CMD_DISPATCH_URL) {}

        void init();
        void step();
        void stop();

    private:
        BridgeService      sitl_bridge_service;
        SitlRequestHandler sitl_request_handler;
    };


    // initialize SimuCopter system
    // (activated from libraries/AP_HAL_SITL/HAL_SITL_Class.cpp)
    void init_simucopter_sitl(void);
}
