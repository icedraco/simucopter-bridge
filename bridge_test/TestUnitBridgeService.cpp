//
// Unit Test Case for BridgeService component
//

#include <cstdlib>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <bridge/BridgeService.h>
#include "test-common.h"

using testing::Eq;
using SIMUCOPTER::BridgeService;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int USEC_SLEEP_AFTER_CLOSE = 1000;
    static const int COMMON_MSG_ID = 1234;

    class DummyRequestHandler: public SIMUCOPTER::AbstractBridgeRequestHandler {
        void handle(const BridgeMessage& msg, BridgeMessage& response) {
            std::stringstream ss_response;
            ss_response << "OK type#" << msg.type << " id#" << msg.id;
            std::string response_str = ss_response.str();
            response.set_data(response_str.c_str(), response_str.length());
        };
    };

    class TestUnitBridgeService: public testing::Test {
    public:
        std::string current_req_url;
        std::string current_cmd_url;
        BridgeMessage msg;
        TestUnitBridgeService() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
        }

    protected:
        virtual void SetUp() {
            current_req_url = get_random_zmq_url();
            current_cmd_url = get_random_zmq_url();
        }
    };
}


TEST_F(TestUnitBridgeService, NotInitializedByDefault) {
    BridgeService service(current_req_url, current_cmd_url);
    ASSERT_FALSE(service.is_initialized());
}

TEST_F(TestUnitBridgeService, InitSetsInitializedFlag) {
    BridgeService service(current_req_url, current_cmd_url);
    ASSERT_FALSE(service.is_initialized()) << "Pre-condition failed: BridgeService is already initialized!";
    service.init();
    ASSERT_TRUE(service.is_initialized());
    service.close();
    usleep(USEC_SLEEP_AFTER_CLOSE);
}

TEST_F(TestUnitBridgeService, CloseUnsetsInitializedFlag) {
    BridgeService service(current_req_url, current_cmd_url);
    service.init();
    ASSERT_TRUE(service.is_initialized());
    service.close();
    usleep(USEC_SLEEP_AFTER_CLOSE);
    ASSERT_FALSE(service.is_initialized());
}

TEST_F(TestUnitBridgeService, HandlerAssignmentWorks) {
    BridgeService service(current_req_url, current_cmd_url);
    DummyRequestHandler handler;

    service.set_request_handler(COMMON_MSG_ID, &handler);
    ASSERT_EQ(&handler, &service.handler(COMMON_MSG_ID));
}

TEST_F(TestUnitBridgeService, UnassignedHandlerLookupReturnsZeroRequestHandler) {
    BridgeService service(current_req_url, current_cmd_url);
    ASSERT_EQ(service.default_handler(), &service.handler(0));
}

TEST_F(TestUnitBridgeService, ClearRequestHandlerWorks) {
    BridgeService service(current_req_url, current_cmd_url);
    DummyRequestHandler handler;

    service.set_request_handler(COMMON_MSG_ID, &handler);
    ASSERT_EQ(&handler, &service.handler(COMMON_MSG_ID));
    service.clear_request_handler(COMMON_MSG_ID);
    ASSERT_EQ(service.default_handler(), &service.handler(COMMON_MSG_ID));
}

//TEST_F(TestUnitBridgeService, UpdateCallWithoutMessagesDoesntBlock) {
//    BridgeService service(current_req_url, current_cmd_url);
//    service.init();
//    service.update();
//    service.close();
//    ASSERT_TRUE(true);
//}
