#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#include "BridgeClient.h"  // NOTE: not "bridge/" because Simulink flattens lib directories!!
#include "simucopter.h"

using namespace SIMUCOPTER;

BridgeClient* G_CLIENT_ARDUPILOT = nullptr;
BridgeClient* G_CLIENT_SITL = nullptr;

SimulinkBridgeInterface* G_ARDUPILOT = nullptr;
SitlBridgeInterface* G_SITL = nullptr;

#ifdef __cplusplus
extern "C" {
#endif

static void bash(const char* full_path) {
    pid_t pid = fork();

    // fork() failed
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    // this is a child process
    if (pid == 0) {
        // NOTE: USE ABSOLUTE PATHS!
        execl("/usr/bin/env", "bash", full_path, (char *) 0);

        // execl() should not return, but if it does...
        perror("execl");
        exit(2);
    }
}

inline static void run_ardupilot(void) {
#ifdef ARDUCOPTER_NAVIO
    bash("/home/pi/simucopter/run-arducopter-navio.sh");
#else 
    bash("/home/pi/simucopter/run-arducopter.sh");
#endif
}

inline static void kill_ardupilot(void) {
    bash("/home/pi/simucopter/kill-arducopter.sh");
}

void simucopter_init(void) {
    run_ardupilot();

    //--- ArduPilot ---//
    fprintf(stdout, "Creating client_ardupilot...\n"); fflush(stdout);
    BridgeClient* client_ardupilot = new BridgeClient(
            SIMUCOPTER::ZMQ_BRIDGE_REQ_URL,
            SIMUCOPTER::ZMQ_BRIDGE_CMD_URL);
    G_CLIENT_ARDUPILOT = client_ardupilot;
    G_CLIENT_ARDUPILOT->init();

    fprintf(stdout, "Creating bi_ardupilot...\n"); fflush(stdout);
    SimulinkBridgeInterface *bi_ardupilot = new SimulinkBridgeInterface(G_CLIENT_ARDUPILOT);
    G_ARDUPILOT = bi_ardupilot;

    //--- SITL ---//
    fprintf(stdout, "Creating client_sitl...\n"); fflush(stdout);
    BridgeClient* client_sitl = new BridgeClient(
            SIMUCOPTER::ZMQ_SITL_REQ_URL,
            SIMUCOPTER::ZMQ_SITL_CMD_URL);
    G_CLIENT_SITL = client_sitl;
    G_CLIENT_SITL->init();

    fprintf(stdout, "Creating bi_sitl...\n"); fflush(stdout);
    SitlBridgeInterface *bi_sitl = new SitlBridgeInterface(G_CLIENT_SITL);
    G_SITL = bi_sitl;

    fprintf(stdout, "simucopter_init() complete!\n"); fflush(stdout);
}

void simucopter_stop(void) {
    if (G_ARDUPILOT != nullptr)
        delete G_ARDUPILOT;

    if (G_SITL != nullptr)
        delete G_SITL;

    if (G_CLIENT_ARDUPILOT != nullptr)
        delete G_CLIENT_ARDUPILOT;

    if (G_CLIENT_SITL!= nullptr)
        delete G_CLIENT_SITL;

    // kill ardupilot
    kill_ardupilot();
}

/*** FLIGHT MODE FUNCTIONS ***************************************************/

double copter_get_accel_x() {
    return G_ARDUPILOT->get_accel_x();
}

double copter_get_accel_y() {
    return G_ARDUPILOT->get_accel_y();
}

double copter_get_accel_z() {
    return G_ARDUPILOT->get_accel_z();
}

double copter_get_gyro_x() {
    return G_ARDUPILOT->get_gyro_x();
}

double copter_get_gyro_y() {
    return G_ARDUPILOT->get_gyro_y();
}

double copter_get_gyro_z() {
    return G_ARDUPILOT->get_gyro_z();
}

double copter_get_state_yaw() {
    return G_ARDUPILOT->get_state_yaw();
}

double copter_get_state_roll() {
    return G_ARDUPILOT->get_state_roll();
}

double copter_get_state_pitch() {
    return G_ARDUPILOT->get_state_pitch();
}

double copter_get_state_throttle() {
    return G_ARDUPILOT->get_state_throttle();
}

double copter_get_desired_yaw() {
    return G_ARDUPILOT->get_desired_yaw();
}

double copter_get_desired_roll() {
    return G_ARDUPILOT->get_desired_roll();
}

double copter_get_desired_pitch() {
    return G_ARDUPILOT->get_desired_pitch();
}

double copter_get_desired_throttle() {
    return G_ARDUPILOT->get_desired_throttle();
}
double copter_get_heading() {
    return G_ARDUPILOT->get_heading();
}
void copter_set_rate_target_yaw(double yaw) {
    G_ARDUPILOT->set_rate_target_yaw(yaw);
}

void copter_set_rate_target_pitch(double pitch) {
    G_ARDUPILOT->set_rate_target_pitch(pitch);
}

void copter_set_rate_target_roll(double roll) {
    G_ARDUPILOT->set_rate_target_roll(roll);
}

void copter_motors_set_roll(double roll) {
    G_ARDUPILOT->motors_set_roll(roll);
}

void copter_motors_set_pitch(double pitch) {
    G_ARDUPILOT->motors_set_pitch(pitch);
}

void copter_motors_set_yaw(double yaw) {
    G_ARDUPILOT->motors_set_yaw(yaw);
}

void copter_motors_set_throttle(double throttle) {
    G_ARDUPILOT->motors_set_throttle(throttle);
}



/*** SITL FUNCTIONS **********************************************************/

double sitl_get_state_yaw() {
    return G_SITL->get_state_yaw();
}

double sitl_get_state_roll() {
    return G_SITL->get_state_roll();
}

double sitl_get_state_pitch() {
    return G_SITL->get_state_pitch();
}

double sitl_get_accel_x() {
    return G_SITL->get_accel_x();
}

double sitl_get_accel_y() {
    return G_SITL->get_accel_y();
}

double sitl_get_accel_z() {
    return G_SITL->get_accel_z();
}

double sitl_get_gyro_x() {
    return G_SITL->get_gyro_x();
}

double sitl_get_gyro_y() {
    return G_SITL->get_gyro_y();
}

double sitl_get_gyro_z() {
    return G_SITL->get_gyro_z();
}

double sitl_get_height() {
    return G_SITL->get_height();
}

double sitl_get_heading() {
    return G_SITL->get_heading();
}

#ifdef __cplusplus
};
#endif
