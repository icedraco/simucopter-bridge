#!/usr/bin/env bash

# This script is responsible for activating ArduPilot. It is triggered by the
# Simulink Agent and is expected to eventually bring up the arducopter process.

ARDUPILOT_ROOT=/home/pi/ardupilot
BOARD_TYPE=navio

# Disable ASLR as a stability workaround
su -c "echo 0 | tee /proc/sys/kernel/randomize_va_space"

cd ${ARDUPILOT_ROOT}
./waf configure --board ${BOARD_TYPE} && \
./waf build --target bin/arducopter -j 4 && \
sudo ./build/${BOARD_TYPE}/bin/arducopter -A tcp:0.0.0.0:5760 -C /dev/ttyAMA0

