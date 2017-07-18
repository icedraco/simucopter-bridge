#!/usr/bin/env bash

# expected location of (augmented) ArduPilot
ARDUPILOT_ROOT="/home/pi/ardupilot"
SIMUCOPTER_ROOT=`pwd`
PATCH_ROOT="${SIMUCOPTER_ROOT}/patch"

# what happens, essentially, is that the changes we made are not yet committed
# to ArduPilot's official git in any way. Those changes git can take, and throw
# into a patch file for us - and it should work!

pushd $ARDUPILOT_ROOT
git diff > ${PATCH_ROOT}/simucopter.patch
popd

# in order to apply the patch:
#   cd ${ARDUPILOT_ROOT}
#   patch -p1 < ${PATCH_ROOT}/simucopter.patch
