#pragma once

//
// INTEGRATION POINT: SimuCopter<->ArduCopter
//
// This file is included from ArduCopter/system.cpp and is used to initiatlize
// the entire SimuCopter system along with its communication bridge.
//


namespace SIMUCOPTER {
    // handles incoming REQUEST messages via ArduCopterRequestHandler
    void request_thread(void);

    // initialize the SimuCopter system (activated from ArduCopter/system.cpp)
    void init_simucopter(void);
}
