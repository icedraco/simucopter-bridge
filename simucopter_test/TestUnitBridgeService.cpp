//
// Unit Test Case for BridgeService component
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BridgeService.h"

using testing::Eq;
using SIMUCOPTER::BridgeService;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int COMMON_MSG_ID = 1234;

    class DummyRequestHandler: public SIMUCOPTER::BridgeRequestHandler {
        void handle(const BridgeMessage& msg, BridgeMessage& response) {
            std::stringstream ss_response;
            ss_response << "OK type#" << msg.type << " id#" << msg.id;
            std::string response_str = ss_response.str();
            response.set_data(response_str.c_str(), response_str.length());
        };
    };

    class TestUnitBridgeService: public testing::Test {
    public:
        BridgeMessage msg;
        BridgeService service;
        DummyRequestHandler handler;

        TestUnitBridgeService() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
            service.set_request_handler(COMMON_MSG_ID, &handler);
        }
    };
}


TEST_F(TestUnitBridgeService, NotInitializedByDefault) {
    ASSERT_FALSE(service.is_initialized());
}

TEST_F(TestUnitBridgeService, InitSetsInitializedFlag) {
    ASSERT_FALSE(service.is_initialized()) << "Pre-condition failed: BridgeService is already initialized!";
    service.init();
    ASSERT_TRUE(service.is_initialized());
}

TEST_F(TestUnitBridgeService, HandlerAssignmentWorks) {
    ASSERT_EQ(&handler, &service.handler(COMMON_MSG_ID));
}

TEST_F(TestUnitBridgeService, UnassignedHandlerLookupReturnsZeroRequestHandler) {
    ASSERT_EQ(service.default_handler(), &service.handler(0));
}

TEST_F(TestUnitBridgeService, ClearRequestHandlerWorks) {
    ASSERT_EQ(&handler, &service.handler(COMMON_MSG_ID));
    service.clear_request_handler(COMMON_MSG_ID);
    ASSERT_EQ(service.default_handler(), &service.handler(COMMON_MSG_ID));
}

TEST_F(TestUnitBridgeService, UpdateCallWithoutMessagesDoesntBlock) {
    service.init();
    service.update();
    ASSERT_TRUE(true);
}
