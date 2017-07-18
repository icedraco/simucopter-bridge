#!/usr/bin/env bash

# This script is responsible for activating ArduPilot. It is triggered by the
# Simulink Agent and is expected to eventually bring up the arducopter process.

ARDUPILOT_ROOT=/home/pi/ardupilot
BOARD_TYPE=sitl

cd ${ARDUPILOT_ROOT}
./waf configure --board ${BOARD_TYPE} && \
./waf build --target bin/arducopter -j 4 && \
./build/${BOARD_TYPE}/bin/arducopter -S -I0 --home '-35.363261,149.165230,584,353' --model 'X' --speedup '1' --defaults ./Tools/autotest/default_params/copter.parm
