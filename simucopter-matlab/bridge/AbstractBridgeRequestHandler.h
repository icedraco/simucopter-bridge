#pragma once

#include "BridgeMessage.h"

namespace SIMUCOPTER {

    /**
     * This is a wrapper class for functionality that handles incoming messages
     * and, optionally, formulates responses to said messages.
     *
     * A service usually creates a BridgeRequestHandler subclass, where it
     * handles a specific incoming message (or several of those), and registers
     * an instance of said subclass with a BridgeService.
     *
     * BridgeService then notifies us by invoking handle() with an incoming
     * message, and a response message prepared for delivery. The data inside
     * that message can be tweaked as necessary before transmission.
     */
    class AbstractBridgeRequestHandler {
    public:
        AbstractBridgeRequestHandler() {}
        virtual ~AbstractBridgeRequestHandler() {}

        /**
         * Handle an incoming BridgeMessage
         * @param msg incoming message
         * @param response response message for the incoming message
         */
        virtual void handle(const BridgeMessage& msg, BridgeMessage& response) = 0;
    };

}
