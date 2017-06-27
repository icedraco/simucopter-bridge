//
// Unit Test Case for AbstractBridgeCommandHandler logic
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bridge/AbstractBridgeCommandHandler.h>

using testing::Eq;
using SIMUCOPTER::AbstractBridgeCommandHandler;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int COMMON_MSG_ID = 1234;

    class DummyBridgeCommandHandler : public AbstractBridgeCommandHandler {
    public:
        int last_id = -1;
        void handle(const BridgeMessage& cmd) {
            last_id = cmd.id;
        }
    };

    class TestUnitAbstractBridgeCommandHandler: public testing::Test {
    public:
        DummyBridgeCommandHandler handler;

        TestUnitAbstractBridgeCommandHandler() :
                handler()
        {
        }
    };
}


TEST_F(TestUnitAbstractBridgeCommandHandler, NotInitializedByDefault) {
    ASSERT_FALSE(handler.is_initialized());
}

TEST_F(TestUnitAbstractBridgeCommandHandler, InitSetsInitializedFlag) {
    ASSERT_FALSE(handler.is_initialized()) << "Pre-condition failed: handler is already initialized!";
    handler.init();
    ASSERT_TRUE(handler.is_initialized());
}

TEST_F(TestUnitAbstractBridgeCommandHandler, HandleNextWithoutPublisherDoesntBlock) {
    handler.init();
    ASSERT_FALSE(handler.handle_next());
}
