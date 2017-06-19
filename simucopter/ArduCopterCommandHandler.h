#pragma  once

// FIXME: This is needed to access some of Copter.h data
#define private public

#include <bridge/AbstractBridgeCommandHandler.h>
#include "SimuCopterMessage.h"
#include "Copter.h"

namespace SIMUCOPTER {

    /**
     * Responsible for handling incoming commands from Simulink
     */
    class ArduCopterCommandHandler: public AbstractBridgeCommandHandler {
    public:
        ArduCopterCommandHandler() {}

        /**
         * This method should be used to check if the underlying system was
         * asked remotely to shut down.
         *
         * @return true if the system was instructed to shut down
         */
        inline bool is_shutdown(void) const { return m_shutdown; }

        /**
         * Handle an incoming remote command
         * @param cmd command
         */
        virtual void handle(const BridgeMessage& cmd);

    private:
        bool m_shutdown = false;
    };

}
