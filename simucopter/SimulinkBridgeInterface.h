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

        double get_flight_mode() { return m_client->request_double(SimuCopterMessage::GET_FLIGHT_MODE); };
        double get_accel_x() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_X); };
        double get_accel_y() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_Y); };
        double get_accel_z() { return m_client->request_double(SimuCopterMessage::GET_ACCEL_Z); };
        double get_gyro_x() { return m_client->request_double(SimuCopterMessage::GET_GYRO_X); };
        double get_gyro_y() { return m_client->request_double(SimuCopterMessage::GET_GYRO_Y); };
        double get_gyro_z() { return m_client->request_double(SimuCopterMessage::GET_GYRO_Z); };
        double get_state_yaw() { return m_client->request_double(SimuCopterMessage::GET_STATE_YAW); };
        double get_state_roll() { return m_client->request_double(SimuCopterMessage::GET_STATE_ROLL); };
        double get_state_pitch() { return m_client->request_double(SimuCopterMessage::GET_STATE_PITCH); };
        double get_desired_yaw() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_YAW); };
        double get_desired_roll() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_ROLL); };
        double get_desired_pitch() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_PITCH); };
        double get_desired_throttle() { return m_client->request_double(SimuCopterMessage::GET_DESIRED_THROTTLE); };
        void set_rate_target_yaw(double yaw) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_YAW, yaw); };
        void set_rate_target_pitch(double pitch) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_PITCH, pitch); };
        void set_rate_target_roll(double roll) { m_client->send_command(SimuCopterMessage::SET_RATE_TARGET_ROLL, roll); };
        void motors_set_roll(double roll) { m_client->send_command(SimuCopterMessage::SET_MOTORS_ROLL, roll); };
        void motors_set_pitch(double pitch) { m_client->send_command(SimuCopterMessage::SET_MOTORS_PITCH, pitch); };
        void motors_set_yaw(double yaw) { m_client->send_command(SimuCopterMessage::SET_MOTORS_YAW, yaw); };
        void motors_set_throttle(double throttle) { m_client->send_command(SimuCopterMessage::SET_MOTORS_THROTTLE, throttle); };

    private:
        BridgeClient* m_client;
    };
}
