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

        inline double get_state_yaw() { return m_client->request_double(SimuCopterMessage::SITL_GET_STATE_YAW); }
        inline double get_state_roll() { return m_client->request_double(SimuCopterMessage::SITL_GET_STATE_ROLL); }
        inline double get_state_pitch() { return m_client->request_double(SimuCopterMessage::SITL_GET_STATE_PITCH); }
        inline double get_accel_x() { return m_client->request_double(SimuCopterMessage::SITL_GET_ACCEL_X); }
        inline double get_accel_y() { return m_client->request_double(SimuCopterMessage::SITL_GET_ACCEL_Y); }
        inline double get_accel_z() { return m_client->request_double(SimuCopterMessage::SITL_GET_ACCEL_Z); }
        inline double get_gyro_x() { return m_client->request_double(SimuCopterMessage::SITL_GET_GYRO_X); }
        inline double get_gyro_y() { return m_client->request_double(SimuCopterMessage::SITL_GET_GYRO_Y); }
        inline double get_gyro_z() { return m_client->request_double(SimuCopterMessage::SITL_GET_GYRO_Z); }
        inline double get_height() { return m_client->request_double(SimuCopterMessage::SITL_GET_HEIGHT); }
        inline double get_heading() { return m_client->request_double(SimuCopterMessage::SITL_GET_HEADING); }

    private:
        BridgeClient* m_client;
    };
}
