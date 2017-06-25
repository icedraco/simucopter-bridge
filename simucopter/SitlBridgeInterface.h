#pragma once

#include <BridgeClient.h>
#include "SimuCopterMessage.h"

namespace SIMUCOPTER {

    /**
     * SimuCopter interface on the Simulink Agent side (SITL)
     *
     * This class facilitates request/command delivery over the
     * Simulink-ArduPilot bridge using the underlying bridge library.
     */
    class SitlBridgeInterface {
    public:
        SitlBridgeInterface(BridgeClient* client) : m_client(client) {
            assert(client->is_initialized());
        }

        inline int whatever() { return m_client->request_int(SimuCopterMessage::SITL_WHATEVER); };

    private:
        BridgeClient* m_client;
    };
}
