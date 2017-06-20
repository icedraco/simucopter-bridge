//
// simucopter.h variant for the ArduCopter side
//

#pragma once

#include <thread>
#include "ArduCopterRequestHandler.h"

namespace SIMUCOPTER {
    void request_thread(void);
    void init_simucopter(void);
}
