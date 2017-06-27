//
// Unit Test Case for the BridgeMessage component
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bridge/BridgeMessage.h>

using testing::Eq;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;
using SIMUCOPTER::BRIDGE_MSG_DATA_CAPACITY;

namespace {
    static const int COMMON_MSG_ID = 1234;
    static const char LOREM[] =
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque vestibulum odio" \
                "et felis ultricies, sed auctor diam sagittis. Quisque nec vestibulum nisi. Sed mattis " \
                "ex egestas, fringilla metus in, aliquet orci. Mauris sed lectus egestas, molestie mauris " \
                "vitae, porttitor sapien. Curabitur finibus sodales vulputate. Etiam lobortis justo non " \
                "sem rutrum aliquam. Fusce viverra, sapien a volutpat dapibus, libero lacus tristique lacus, " \
                "in scelerisque ligula diam vitae justo. Donec elementum varius lectus in laoreet.";

    class TestUnitBridgeMessage : public testing::Test {
    public:
        BridgeMessage commonMsg;
        TestUnitBridgeMessage() : commonMsg(BridgeMessageType::REQUEST, COMMON_MSG_ID) {}
    };
}


TEST_F(TestUnitBridgeMessage, MessageIdMatchesContructorArgument) {
    ASSERT_EQ(0x1337, BridgeMessage(BridgeMessageType::REQUEST, 0x1337).id);
}

TEST_F(TestUnitBridgeMessage, MessageTypeMatchesContructorArgument) {
    ASSERT_EQ(BridgeMessageType::REQUEST, BridgeMessage(BridgeMessageType::REQUEST, 0x1337).type);
}

TEST_F(TestUnitBridgeMessage, DefaultMessageSizeIsZero) {
    ASSERT_EQ(0, commonMsg.size());
}

TEST_F(TestUnitBridgeMessage, DefaultGetDataStoresZeroBytes) {
    char buffer[1024] = "here be dragons";
    ASSERT_EQ(0, commonMsg.load_data(buffer, 1024));
    ASSERT_STREQ("here be dragons", buffer);
}

TEST_F(TestUnitBridgeMessage, GetReplyMethodReturnsProperMessageInstance) {
    BridgeMessage reply = commonMsg.get_reply();
    ASSERT_EQ(BridgeMessageType::REPLY, reply.type);
    ASSERT_EQ(commonMsg.id, reply.id);
    ASSERT_EQ(0, reply.size());
}

TEST_F(TestUnitBridgeMessage, SetDataDoesNotExceedCapacity) {
    ASSERT_GT(sizeof(LOREM), BRIDGE_MSG_DATA_CAPACITY);
    ASSERT_EQ(BRIDGE_MSG_DATA_CAPACITY, commonMsg.set_data(LOREM, sizeof(LOREM)));
    ASSERT_EQ(BRIDGE_MSG_DATA_CAPACITY, commonMsg.size());

    char cmp_buffer[1024];
    memcpy(cmp_buffer, LOREM, sizeof(LOREM));
    cmp_buffer[BRIDGE_MSG_DATA_CAPACITY] = '\0';

    char buffer[1024];
    memset(buffer, 0, 1024);
    ASSERT_EQ(BRIDGE_MSG_DATA_CAPACITY, commonMsg.load_data(buffer, 1024));
    ASSERT_EQ(BRIDGE_MSG_DATA_CAPACITY, strlen(buffer));
    ASSERT_TRUE(strncmp(buffer, cmp_buffer, 1024) == 0);
}
