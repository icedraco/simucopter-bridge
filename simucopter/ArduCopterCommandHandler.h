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
         * Start handling commands
         */
        inline void start(void) { m_active = true; }

        /**
         * Stop (i.e., pause) handling commands
         * All commands missed while the handler is stopped will be discarded.
         */
        inline void stop(void) { m_active = false; }

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
        bool m_active = false;
        bool m_shutdown = false;
    };

}
