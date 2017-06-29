#include "simucopter-sitl.h"


namespace SIMUCOPTER {

    SimucopterSitlServer sitlServer;

    void SimucopterSitlServer::init() {
        sitl_bridge_service.init();
        sitl_request_handler.register_self(sitl_bridge_service);
        hal.scheduler->register_timer_process(FUNCTOR_BIND_MEMBER(&SimucopterSitlServer::step, void));
    }

    void SimucopterSitlServer::step() {
        if (sitl_request_handler.connected) {
            sitl_bridge_service.update();
        } else {
            if (sitl_request_handler.connect_sitl()) {
                printf("SitlRequestHandler <-> SITL connection established!\n");
            }
        }
    }

    void SimucopterSitlServer::stop() {
        sitl_bridge_service.close();
    }

    void init_simucopter_sitl(void) {
        sitlServer.init();
        printf("init_simucopter_sitl() - OK\n");
    }
}

