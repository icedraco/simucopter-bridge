#pragma once

#include <BridgeClient.h>
#include "SimuCopterMessage.h"

namespace SIMUCOPTER {

    /**
     * SimuCopter interface on the Simulink Agent side
     *
     * This class facilitates request/command delivery over the
     * Simulink-ArduPilot bridge using the underlying bridge library.
     */
    class SimulinkBridgeInterface {
    public:
        SimulinkBridgeInterface(BridgeClient* client) : m_client(client) {
            assert(client->is_initialized());
        }

        inline double get_flight_mode() { return m_client->request_double(SimuCopterMessage::GET_FLIGHT_MODE); };
        inline double get_accel_x() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_X); };
        inline double get_accel_y() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_Y); };
        inline double get_accel_z() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_Z); };
        inline double get_gyro_x() { return m_client->request_double(SimuCopterMessage::GET_GYRO_X); };
        inline double get_gyro_y() { return m_client->request_double(SimuCopterMessage::GET_GYRO_Y); };
        inline double get_gyro_z() { return m_client->request_double(SimuCopterMessage::GET_GYRO_Z); };
        inline double get_state_yaw() { return m_client->request_double(SimuCopterMessage::GET_STATE_YAW); };
        inline double get_state_roll() { return m_client->request_double(SimuCopterMessage::GET_STATE_ROLL); };
        inline double get_state_pitch() { return m_client->request_double(SimuCopterMessage::GET_STATE_PITCH); };
        inline double get_state_throttle() { return m_client->request_double(SimuCopterMessage::GET_STATE_THROTTLE); };
        inline double get_desired_yaw() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_YAW); };
        inline double get_desired_roll() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_ROLL); };
        inline double get_desired_pitch() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_PITCH); };
        inline double get_desired_throttle() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_THROTTLE); };
        inline double get_heading() { return m_client->request_double(SimuCopterMessage::GET_HEADING); };
        inline void set_rate_target_yaw(double yaw) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_YAW, yaw); };
        inline void set_rate_target_pitch(double pitch) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_PITCH, pitch); };
        inline void set_rate_target_roll(double roll) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_ROLL, roll); };
        inline void motors_set_roll(double roll) { m_client->send_command(SimuCopterMessage::SET_MOTORS_ROLL, roll); };
        inline void motors_set_pitch(double pitch) { m_client->send_command(SimuCopterMessage::SET_MOTORS_PITCH, pitch); };
        inline void motors_set_yaw(double yaw) { m_client->send_command(SimuCopterMessage::SET_MOTORS_YAW, yaw); };
        inline void motors_set_throttle(double throttle) { m_client->send_command(SimuCopterMessage::SET_MOTORS_THROTTLE, throttle); };

    private:
        BridgeClient* m_client;
    };
}
