#include "simucopter-arducopter.h"


namespace SIMUCOPTER {
    BridgeService            simucopter_bridge_service("tcp://127.0.0.1:5555", "tcp://127.0.0.1:5556");
    ArduCopterRequestHandler simucopter_request_handler;
	std::thread*             simucopter_request_thread;

    void request_thread(void) {
	    simucopter_bridge_service.init();
	    simucopter_request_handler.register_self(simucopter_bridge_service);
	    while(true) {
            simucopter_bridge_service.update();
            usleep(1000);
	    }
	}

	void init_simucopter(void) {
        simucopter_request_thread = new std::thread(request_thread);
	}
}

