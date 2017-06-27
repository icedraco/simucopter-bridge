#pragma once

#ifdef __cplusplus

#include "SimulinkBridgeInterface.h"
#include "SitlBridgeInterface.h"


extern "C" {
#endif

void simucopter_init();
void simucopter_stop();


/*****************************************************************************\
 * SimuCopter Block Functions ************************************************
\*****************************************************************************/

//--- ArduCopter ------------------------------------------------------------//
double copter_get_accel_x();
double copter_get_accel_y();
double copter_get_accel_z();
double copter_get_gyro_x();
double copter_get_gyro_y();
double copter_get_gyro_z();
double copter_get_state_yaw();
double copter_get_state_roll();
double copter_get_state_pitch();
double copter_get_state_throttle();
double copter_get_desired_yaw();
double copter_get_desired_roll();
double copter_get_desired_pitch();
double copter_get_desired_throttle();
void copter_set_rate_target_yaw(double yaw);
void copter_set_rate_target_pitch(double pitch);
void copter_set_rate_target_roll(double roll);
void copter_motors_set_roll(double roll);
void copter_motors_set_pitch(double pitch);
void copter_motors_set_yaw(double yaw);
void copter_motors_set_throttle(double throttle);
void copter_gcs_send_text(int severity, const char* str);


//--- SITL ------------------------------------------------------------------//
double sitl_get_state_yaw();
double sitl_get_state_roll();
double sitl_get_state_pitch();
double sitl_get_accel_x();
double sitl_get_accel_y();
double sitl_get_accel_z();
double sitl_get_gyro_x();
double sitl_get_gyro_y();
double sitl_get_gyro_z();
double sitl_get_height();
double sitl_get_heading();

#ifdef __cplusplus
};
#endif
