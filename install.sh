#!/usr/bin/env bash
#
# IMPORTANT: Run this script as the 'pi' user!
#            Running this as any other user (e.g., root) will assign wrong
#            values to variables like $HOME
#
#
# NOTE: DO NOT SYMLINK FILES INTO ArduCopter DIRECTORY!
#       Simlinks are dynamically created and destroyed by the installation
#       procedure!
#


# expected location of ArduPilot
ARDUPILOT_ROOT="${HOME}/ardupilot"

# simucopter source and install files - you're supposed to be running it from
# within such a folder.
SIMUCOPTER_ROOT=`pwd`

# where simucopter shell scripts should be installed
# (Required to be in sync with Simulink! DO NOT change!)
SIMUCOPTER_TARGET="${HOME}/simucopter"

APT_PACKAGES="
    python-matplotlib python-serial python-wxgtk2.8 python-wxtools python-lxml
    python-scipy python-opencv ccache gawk git python-pip python-pexpect
    libzmq3-dev"

PIP_PACKAGES="future pymavlink MAVProxy"

###############################################################################

# augment pushd and popd to not pollute stdout
pushd () {
    command pushd "$@" > /dev/null
}

popd () {
    command popd "$@" > /dev/null
}

# this installs a clean version of ArduPilot from GitHub
do_install_ardupilot () {
    set -e  # abort on non-zero return code (important!)
    pushd ${HOME}

    git clone https://github.com/ArduPilot/ardupilot
    cd ardupilot
    git submodule update --init --recursive

    popd
    set +e  # DISABLE abort on non-zero return code (important!)
}

# this prepares the current install dir for deployment
do_install_source_tree () {
    echo "  > making all local scripts executable..."
    chmod u+x ./*.sh

    echo "  > updating 'bridge' and 'simucopter' folders in simucopter-matlab..."
    pushd simucopter-matlab
    rm -vrf bridge simucopter
    cp -vr ../bridge ../simucopter ./
    popd
}

###############################################################################

echo
echo "--- SimuCopter System Installer Script 2.0 -----------------------------"
echo
echo ">>> Locating ArduPilot"
if [ ! -d "${ARDUPILOT_ROOT}" ]; then
    echo "  > ArduPilot directory not found at ${ARDUPILOT_ROOT}!"
    echo "  > Attempt to install it from GitHub?"
    select ans in "Install from GitHub (recommended)" "Build SimuCopter tree only (agent-side)" "Quit"; do
        case ${ans} in
            "Install from GitHub (recommended)" ) do_install_ardupilot; break;;
            "Build SimuCopter tree only (agent-side)" ) do_install_source_tree; exit;;
            "Quit" ) exit;;
        esac
    done

    # verify
    if [ ! -d "${ARDUPILOT_ROOT}" ]; then
        "FATAL: ArduPilot root still not found! Please resolve this before continuing..."
        exit 1
    fi
fi


echo
echo ">>> Installing prerequisites..."
sudo apt -y install ${APT_PACKAGES}
sudo pip install ${PIP_PACKAGES}

echo
echo ">>> Preparing source tree..."
do_install_source_tree

echo
echo ">>> Installing SimuCopter system..."
echo
echo "WARNING: We are about to start augmenting ArduPilot! If you do not want"
echo "         to modify it yet, press CTRL+C now to abort execution!"
echo

# prompt user
select ans in "Continue" "Abort"; do
    case ${ans} in
        "Continue" ) break;;
        "Abort" ) exit;;
    esac
done

# fetch absolute path for the patch folder for later
if [ ! -d "patch" ]; then
    echo "FATAL: Cannot locate the 'patch' subfolder!"
    exit 1
else
    pushd patch
    PATCH_ROOT=`pwd`
    popd
fi

echo
echo "  > ARDUPILOT_ROOT:    ${ARDUPILOT_ROOT}"
echo "  > SIMUCOPTER_ROOT:   ${SIMUCOPTER_ROOT}"
echo "  > SIMUCOPTER_TARGET: ${SIMUCOPTER_TARGET}"
echo "  > PATCH_ROOT:        ${PATCH_ROOT}"
echo

echo "  * Making sure simucopter scripts are accessible..."
if [ ! -d "${SIMUCOPTER_TARGET}" ]; then
    mkdir -p ${SIMUCOPTER_TARGET}
fi

if [ ! -f "${SIMUCOPTER_TARGET}/kill-arducopter.sh" ]; then
    ln -vs `pwd`/kill-arducopter.sh ${SIMUCOPTER_TARGET}/
fi

if [ ! -f "${SIMUCOPTER_TARGET}/run-arducopter.sh" ]; then
    ln -vs `pwd`/run-arducopter.sh ${SIMUCOPTER_TARGET}/
fi

if [ ! -f "${SIMUCOPTER_TARGET}/run-arducopter-navio.sh" ]; then
    ln -vs `pwd`/run-arducopter-navio.sh ${SIMUCOPTER_TARGET}/
fi

chmod +x ${SIMUCOPTER_TARGET}/*.sh

echo "  * Copying/linking SimuCopter files into ArduPilot..."
echo "      > ArduCopter files..."
ln -vs "${SIMUCOPTER_ROOT}/simucopter/control_simulink.cpp" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/simucopter-arducopter.cpp" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/simucopter-arducopter.h" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/SimuCopterMessage.h" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/ArduCopterCommandHandler.cpp" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/ArduCopterCommandHandler.h" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/ArduCopterRequestHandler.cpp" "${ARDUPILOT_ROOT}/ArduCopter/"
ln -vs "${SIMUCOPTER_ROOT}/simucopter/ArduCopterRequestHandler.h" "${ARDUPILOT_ROOT}/ArduCopter/"

echo "      > general bridge library"
ln -vs "${SIMUCOPTER_ROOT}/bridge" "${ARDUPILOT_ROOT}/libraries/bridge"

echo "  * Checking if SimuCopter patch is needed..."
grep --quiet simucopter "${ARDUPILOT_ROOT}/ArduCopter/system.cpp"
if [ "$?" != "0" ]; then
    echo "      > applying SimuCopter patch..."
    pushd ${ARDUPILOT_ROOT}
    patch -p1 < "${PATCH_ROOT}/simucopter.patch"
    popd
else
    echo "      - patch already applied - skipping this step"
fi


echo
echo "### DEPLOYMENT COMPLETE"
echo " # you may now copy the 'simucopter-matlab' folder to the PC with MATLAB"
echo
exit 0
