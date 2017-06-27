//
// Unit Test Case for ZmqBridgeMessageSerializer component
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <bridge/ZmqBridgeMessageSerializer.h>

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
    char buffer[1024];
    size_t pkt_sz = serializer.serialize(msg, buffer, 1024);
    ASSERT_GT(pkt_sz, 0);
    ASSERT_LT(pkt_sz, 1024);
    BridgeMessage result = serializer.deserialize(buffer, pkt_sz);
    ASSERT_EQ(msg.id, result.id);
    ASSERT_EQ(msg.type, result.type);
    ASSERT_EQ(msg.size(), result.size());
}

TEST_F(TestUnitZmqMessageSerializer, SerializationLoopWithMessage) {
    char text[] = "Stuff goes here";
    msg.set_data(text, sizeof(text));

    char buffer[1024];
    size_t pkt_sz = serializer.serialize(msg, buffer, 1024);
    ASSERT_GT(pkt_sz, 0);
    ASSERT_LT(pkt_sz, 1024);
    BridgeMessage result = serializer.deserialize(buffer, pkt_sz);
    ASSERT_EQ(msg.id, result.id);
    ASSERT_EQ(msg.type, result.type);
    ASSERT_EQ(msg.size(), result.size());

    char result_text[1024];
    ASSERT_EQ(msg.size(), result.load_data(result_text, 1024));
    ASSERT_STREQ(text, result_text);
}
