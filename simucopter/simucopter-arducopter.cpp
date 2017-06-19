#include "simucopter-arducopter.h"


void SIMUCOPTER::request_thread(BridgeService &service) {
    simucopter_bridge_service.init();
    simucopter_request_handler.register_self(simucopter_bridge_service);
}

void SIMUCOPTER::init_simucopter(void) {
    std::thread t(request_thread, simucopter_bridge_service);
}
