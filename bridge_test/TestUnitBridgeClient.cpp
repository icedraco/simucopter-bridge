//
// Unit Test Case for BridgeClient component
//

#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bridge/BridgeClient.h>

using testing::Eq;
using SIMUCOPTER::BridgeClient;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int COMMON_MSG_ID = 1234;

    class TestUnitBridgeClient: public testing::Test {
    public:
        BridgeMessage msg;
        TestUnitBridgeClient() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
        }
    };

    void command_receiver(zmq::socket_t* ssub, int* counter) {
        printf("Thread started!\n");
        *counter = 0;
        SIMUCOPTER::ZmqBridgeMessageSerializer serializer;
        bool depleted = false;
        while (*counter == 0 || !depleted) {
            zmq::message_t msg;
            depleted = !ssub->recv(&msg, ZMQ_NOBLOCK);
            if (!depleted) {
                BridgeMessage bm = serializer.deserialize(msg.data(), msg.size());
//                printf(">> Caught a message! (%d) id:%d type:%d\n", *counter, bm.id, bm.type);
                if (bm.id == COMMON_MSG_ID) {
                    (*counter)++;
//                    printf("!! Found a BridgeMessage :D\n");
                }
            }
        }
    }
}


TEST_F(TestUnitBridgeClient, NotInitializedByDefault) {
    BridgeClient client;
    ASSERT_FALSE(client.is_initialized());
}

TEST_F(TestUnitBridgeClient, InitSetsInitializedFlag) {
    BridgeClient client;
    ASSERT_FALSE(client.is_initialized()) << "Pre-condition failed: BridgeClient is already initialized!";
    client.init();
    ASSERT_TRUE(client.is_initialized());
    client.close();
}

TEST_F(TestUnitBridgeClient, CloseUnsetsInitializedFlag) {
    BridgeClient client;
    ASSERT_FALSE(client.is_initialized()) << "Pre-condition failed: BridgeClient is already initialized!";
    client.init();
    ASSERT_TRUE(client.is_initialized());
    client.close();
    ASSERT_FALSE(client.is_initialized());
}

TEST_F(TestUnitBridgeClient, CommandWithoutServiceTimesOut) {
    BridgeClient client;
    client.init();
    client.send_command(COMMON_MSG_ID);
    client.send_command(COMMON_MSG_ID, 0.01);
    client.send_command(COMMON_MSG_ID, 0.01, 0.02);
    client.close();
    ASSERT_TRUE(true);
}

TEST_F(TestUnitBridgeClient, SendCommandArrivesAtDestination) {
    std::string cmd_url = "tcp://127.0.0.1:31337";

    zmq::context_t& ctx = SIMUCOPTER::ZmqContextContainer::get_context();
    zmq::socket_t ssub(ctx, ZMQ_SUB);
    ssub.bind(cmd_url);
    ssub.setsockopt(ZMQ_RCVTIMEO, -1);
    ssub.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    BridgeClient client(SIMUCOPTER::ZMQ_BRIDGE_REQ_URL, cmd_url);
    client.init();

    int counter = 0;
    std::thread t(command_receiver, &ssub, &counter);

    usleep(500000);
    client.send_command(COMMON_MSG_ID);
    client.send_command(COMMON_MSG_ID);
    client.send_command(COMMON_MSG_ID);

    t.join();
    ssub.close();
    client.close();
    ASSERT_GT(counter, 0);
}
