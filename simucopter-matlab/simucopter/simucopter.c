#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "simucopter.h"

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
    simucopter_agent_init();
}

void simucopter_stop(void) {
    simucopter_agent_stop();
}
