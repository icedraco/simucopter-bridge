#pragma  once

#include <simucopter.h>
#include <AbstractBridgeCommandHandler.h>

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
        virtual void handle(const BridgeMessage& cmd) const;

    private:
        bool m_shutdown = false;
    };

}
