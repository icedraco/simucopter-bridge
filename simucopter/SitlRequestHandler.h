#pragma once

//
// SITL REQUEST Message Handler
//
// This component is responsible for handling incoming REQUEST messages from
// the Simulink Agent
//

#define private public

#include <AP_HAL/AP_HAL.h>
#include <AP_HAL_SITL/AP_HAL_SITL.h>
#include <AP_AHRS/AP_AHRS.h>
#include <SITL/SIM_Aircraft.h>

#include <bridge/AbstractBridgeRequestHandler.h>
#include <bridge/BridgeService.h>

#include "SimuCopterMessage.h"

extern const AP_HAL::HAL& hal;

namespace SIMUCOPTER {

    /**
     * Responsible for handling incoming requests from Simulink and responding
     * with the results taken from the underlying ArduCopter system.
     */
    class SitlRequestHandler: public AbstractBridgeRequestHandler {
    public:
        bool connected = false;
        bool connect_sitl(void);
        void register_self(BridgeService& service);
        virtual void handle(const BridgeMessage& msg, BridgeMessage& response);


    private:
        SITL::SITL* m_sitl = nullptr;
        SITL::Aircraft* m_sitl_model = nullptr;
        AP_Baro* m_barometer = nullptr;

        const ArgumentPacker m_packer;
    };

}
