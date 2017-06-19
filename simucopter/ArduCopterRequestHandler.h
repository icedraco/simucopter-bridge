#pragma once

#include <AbstractBridgeRequestHandler.h>
#include <BridgeService.h>
#include "SimuCopterMessage.h"

namespace SIMUCOPTER {

    /**
     * Responsible for handling incoming requests from Simulink and responding
     * with the results taken from the underlying ArduCopter system.
     */
    class ArduCopterRequestHandler: public AbstractBridgeRequestHandler {
    public:
        void register_self(BridgeService& service) const;
        virtual void handle(const BridgeMessage& msg, BridgeMessage& response) const;
    };

}