#include <unistd.h>
#include "simucopter.h"

using namespace SIMUCOPTER;

BridgeClient* G_CLIENT_ARDUPILOT = nullptr;
BridgeClient* G_CLIENT_SITL = nullptr;

SimulinkBridgeInterface* ardupilot = nullptr;
SitlBridgeInterface* sitl = nullptr;

#ifdef __cplusplus
extern "C" {
#endif

static void run_ardupilot(void) {
    // executed by flight mode init function: SomeFlightMode_init()

    uid_t uid;

    // --> find the name of current executable (i.e., flight mode name hint)
    char exe[1024];
    ssize_t len = readlink("/proc/self/exe", exe, 1024);
    if (len != -1) {
        exe[len] = '\0';
    } else {
        exe[0] = '\0';
        perror("readlink");
        exit(1);
    }

    // --> launch simutool
    pid_t pid = fork();

    // fork() failed
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    // this is a child process
    if (pid == 0) {
        // NOTE: USE ABSOLUTE PATHS!
        execl("/usr/bin/env", "bash", "/home/pi/simucopter/run-arducopter.sh", (char *) 0);

        // execl() should not return, but if it does...
        perror("execl");
        exit(2);
    }
}

void simucopter_init(void) {
    run_ardupilot();

    //--- ArduPilot ---//
    BridgeClient* client_ardupilot = new BridgeClient(
            SIMUCOPTER::ZMQ_BRIDGE_REQ_URL,
            SIMUCOPTER::ZMQ_BRIDGE_CMD_URL);
    G_CLIENT_ARDUPILOT = client_ardupilot;
    G_CLIENT_ARDUPILOT->init();

    SimulinkBridgeInterface *bi_ardupilot = new SimulinkBridgeInterface(G_CLIENT_ARDUPILOT);
    ardupilot = bi_ardupilot;

    //--- SITL ---//
    BridgeClient* client_sitl = new BridgeClient(
            SIMUCOPTER::ZMQ_SITL_REQ_URL,
            SIMUCOPTER::ZMQ_SITL_CMD_URL);
    G_CLIENT_SITL = client_sitl;
    G_CLIENT_SITL->init();

    SitlBridgeInterface *bi_sitl = new SitlBridgeInterface(G_CLIENT_SITL);
    sitl = bi_sitl;
}

void simucopter_stop(void) {
    // TODO: send SHUTDOWN signal

    if (ardupilot != nullptr)
        delete ardupilot;

    if (sitl != nullptr)
        delete sitl;

    if (G_CLIENT_ARDUPILOT != nullptr)
        delete G_CLIENT_ARDUPILOT;

    if (G_CLIENT_SITL!= nullptr)
        delete G_CLIENT_SITL;
}

/*** FLIGHT MODE FUNCTIONS ***************************************************/

double copter_get_accel_x() {
    return ardupilot->get_accel_x();
}

double copter_get_accel_y() {
    return ardupilot->get_accel_y();
}

double copter_get_accel_z() {
    return ardupilot->get_accel_z();
}

double copter_get_gyro_x() {
    return ardupilot->get_gyro_x();
}

double copter_get_gyro_y() {
    return ardupilot->get_gyro_y();
}

double copter_get_gyro_z() {
    return ardupilot->get_gyro_z();
}

double copter_get_state_yaw() {
    return ardupilot->get_state_yaw();
}

double copter_get_state_roll() {
    return ardupilot->get_state_roll();
}

double copter_get_state_pitch() {
    return ardupilot->get_state_pitch();
}

double copter_get_desired_yaw() {
    return ardupilot->get_desired_yaw();
}

double copter_get_desired_roll() {
    return ardupilot->get_desired_roll();
}

double copter_get_desired_pitch() {
    return ardupilot->get_desired_pitch();
}

double copter_get_desired_throttle() {
    return ardupilot->get_desired_throttle();
}

void copter_set_rate_target_yaw(double yaw) {
    ardupilot->set_rate_target_yaw(yaw);
}

void copter_set_rate_target_pitch(double pitch) {
    ardupilot->set_rate_target_pitch(pitch);
}

void copter_set_rate_target_roll(double roll) {
    ardupilot->set_rate_target_roll(roll);
}

void copter_motors_set_roll(double roll) {
    ardupilot->motors_set_roll(roll);
}

void copter_motors_set_pitch(double pitch) {
    ardupilot->motors_set_pitch(pitch);
}

void copter_motors_set_yaw(double yaw) {
    ardupilot->motors_set_yaw(yaw);
}

void copter_motors_set_throttle(double throttle) {
    ardupilot->motors_set_throttle(throttle);
}

double sitl_whatever() {
    return sitl->whatever();
}

#ifdef __cplusplus
};
#endif
