//
// ArduCopter Entry Point
//
// This file is included from ArduCopter/system.cpp and is used to initiatlize
// the entire SimuCopter system along with its communication bridge.
//

#include <unistd.h>
#include <thread>
#include <bridge/BridgeService.h>

#include "ArduCopterRequestHandler.h"
#include "simucopter-arducopter.h"

namespace SIMUCOPTER {
    // provides message I/O between Simulink Agent and ArduCopter
    BridgeService simucopter_bridge_service(ZMQ_BRIDGE_REQ_URL, ZMQ_BRIDGE_CMD_URL, ZMQ_BRIDGE_CMD_DISPATCH_URL);

    // handles incoming REQUEST messages via a BridgeService instance
    ArduCopterRequestHandler simucopter_request_handler;

    // see request_thread()
	std::thread* simucopter_request_thread;


    void request_thread(void) {
	    simucopter_bridge_service.init();
	    simucopter_request_handler.register_self(simucopter_bridge_service);
	    while(true) {
            simucopter_bridge_service.update();
            usleep(1000 /* usec */);  // TODO: Magic Number - extract into a constant
	    }
	}

	void init_simucopter(void) {
        simucopter_request_thread = new std::thread(request_thread);
	}
}

