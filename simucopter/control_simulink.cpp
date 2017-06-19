//
// This file contains ArduPilot flight mode for SIMULINK
//

#include <ArduCopterCommandHandler.h>
#include "Copter.h"

namespace SIMUCOPTER {
    ArduCopterCommandHandler handler;
}

bool Copter::simulink_init(bool ignore_checks) {
    if (!SIMUCOPTER::handler.is_initialized())
        SIMUCOPTER::handler.init();
    return true;
}

void Copter::simulink_run() {
    SIMUCOPTER::handler.handle_next();
}
