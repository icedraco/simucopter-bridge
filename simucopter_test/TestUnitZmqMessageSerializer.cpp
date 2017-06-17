//
// Unit Test Case for ZmqBridgeMessageSerializer component
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ZmqBridgeMessageSerializer.h"

using testing::Eq;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;
using SIMUCOPTER::ZmqBridgeMessageSerializer;

namespace {
    static const int COMMON_MSG_ID = 1234;

    class TestUnitZmqMessageSerializer: public testing::Test {
    public:
        BridgeMessage msg;
        ZmqBridgeMessageSerializer serializer;

        TestUnitZmqMessageSerializer() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
        }
    };
}


TEST_F(TestUnitZmqMessageSerializer, SerializationLoopWithoutMessage) {
    BridgeMessage result = serializer.deserialize(serializer.serialize(msg));
    ASSERT_EQ(msg.id, result.id);
    ASSERT_EQ(msg.type, result.type);
    ASSERT_EQ(msg.size(), result.size());
}

TEST_F(TestUnitZmqMessageSerializer, SerializationLoopWithMessage) {
    char text[] = "Stuff goes here";
    msg.set_data(text, sizeof(text));

    BridgeMessage result = serializer.deserialize(serializer.serialize(msg));
    ASSERT_EQ(msg.id, result.id);
    ASSERT_EQ(msg.type, result.type);
    ASSERT_EQ(msg.size(), result.size());

    char result_text[1024];
    ASSERT_EQ(msg.size(), result.load_data(result_text, 1024));
    ASSERT_STREQ(text, result_text);
}
