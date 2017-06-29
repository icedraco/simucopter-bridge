#include "SimulinkBridgeInterface.h"

double SIMUCOPTER::SimulinkBridgeInterface::get_flight_mode() {
    return m_client.request_double(SimuCopterMessage::GET_FLIGHT_MODE);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_accel_x() {
    return m_client.request_double(SimuCopterMessage::GET_ACCEL_X);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_accel_y() {
    return m_client.request_double(SimuCopterMessage::GET_ACCEL_Y);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_accel_z() {
    return m_client.request_double(SimuCopterMessage::GET_ACCEL_Z);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_gyro_x() {
    return m_client.request_double(SimuCopterMessage::GET_GYRO_X);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_gyro_y() {
    return m_client.request_double(SimuCopterMessage::GET_GYRO_Y);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_gyro_z() {
    return m_client.request_double(SimuCopterMessage::GET_GYRO_Z);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_state_yaw() {
    return m_client.request_double(SimuCopterMessage::GET_STATE_YAW);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_state_roll() {
    return m_client.request_double(SimuCopterMessage::GET_STATE_ROLL);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_state_pitch() {
    return m_client.request_double(SimuCopterMessage::GET_STATE_PITCH);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_desired_yaw() {
    return m_client.request_double(SimuCopterMessage::GET_DESIRED_YAW);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_desired_roll() {
    return m_client.request_double(SimuCopterMessage::GET_DESIRED_ROLL);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_desired_pitch() {
    return m_client.request_double(SimuCopterMessage::GET_DESIRED_PITCH);
}

double SIMUCOPTER::SimulinkBridgeInterface::get_desired_throttle() {
    return m_client.request_double(SimuCopterMessage::GET_DESIRED_THROTTLE);
}
double SIMUCOPTER::SimulinkBridgeInterface::get_heading() {
    return m_client.request_double(SimuCopterMessage::GET_HEADING);
}
void SIMUCOPTER::SimulinkBridgeInterface::set_rate_target_yaw(double yaw) {
    m_client.send_command(SimuCopterMessage::SET_RATE_TARGET_YAW, yaw);
}

void SIMUCOPTER::SimulinkBridgeInterface::set_rate_target_pitch(double pitch) {
    m_client.send_command(SimuCopterMessage::SET_RATE_TARGET_PITCH, pitch);
}

void SIMUCOPTER::SimulinkBridgeInterface::set_rate_target_roll(double roll) {
    m_client.send_command(SimuCopterMessage::SET_RATE_TARGET_ROLL, roll);
}

void SIMUCOPTER::SimulinkBridgeInterface::motors_set_roll(double roll) {
    m_client.send_command(SimuCopterMessage::SET_MOTORS_ROLL, roll);
}

void SIMUCOPTER::SimulinkBridgeInterface::motors_set_pitch(double pitch) {
    m_client.send_command(SimuCopterMessage::SET_MOTORS_PITCH, pitch);
}

void SIMUCOPTER::SimulinkBridgeInterface::motors_set_yaw(double yaw) {
    m_client.send_command(SimuCopterMessage::SET_MOTORS_YAW, yaw);
}

void SIMUCOPTER::SimulinkBridgeInterface::motors_set_throttle(double throttle) {
    m_client.send_command(SimuCopterMessage::SET_MOTORS_THROTTLE, throttle);
}

