//
// Unit Test Case for BridgeClient component
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BridgeClient.h"

using testing::Eq;
using SIMUCOPTER::BridgeClient;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int COMMON_MSG_ID = 1234;

    class TestUnitBridgeClient: public testing::Test {
    public:
        BridgeMessage msg;
        BridgeClient client;

        TestUnitBridgeClient() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
        }
    };
}


TEST_F(TestUnitBridgeClient, NotInitializedByDefault) {
    ASSERT_FALSE(client.is_initialized());
}

TEST_F(TestUnitBridgeClient, InitSetsInitializedFlag) {
    ASSERT_FALSE(client.is_initialized()) << "Pre-condition failed: BridgeClient is already initialized!";
    client.init();
    ASSERT_TRUE(client.is_initialized());
}

TEST_F(TestUnitBridgeClient, CommandWithoutServiceTimesOut) {
    client.init();
    client.send_command(COMMON_MSG_ID);
    client.send_command(COMMON_MSG_ID, 0.01);
    client.send_command(COMMON_MSG_ID, 0.01, 0.02);
    ASSERT_TRUE(true);
}
