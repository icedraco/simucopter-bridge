#pragma once

#define private public

#include <bridge/AbstractBridgeRequestHandler.h>
#include <bridge/BridgeService.h>
#include <bridge/ArgumentPacker.h>
#include "SimuCopterMessage.h"
#include "Copter.h"

namespace SIMUCOPTER {

    /**
     * Responsible for handling incoming requests from Simulink and responding
     * with the results taken from the underlying ArduCopter system.
     */
    class ArduCopterRequestHandler: public AbstractBridgeRequestHandler {
    public:
        void register_self(BridgeService& service);
        virtual void handle(const BridgeMessage& msg, BridgeMessage& response);

    private:
        const ArgumentPacker m_packer;
    };

}
