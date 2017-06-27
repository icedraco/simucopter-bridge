//
// Integration tests between BridgeClient and BridgeService
//


#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bridge/AbstractBridgeCommandHandler.h>
#include <bridge/BridgeClient.h>
#include <bridge/BridgeService.h>
#include "test-common.h"

using testing::Eq;
using SIMUCOPTER::BridgeClient;
using SIMUCOPTER::BridgeService;
using SIMUCOPTER::BridgeMessage;
using SIMUCOPTER::BridgeMessageType;

namespace {
    static const int COMMON_MSG_ID = 1234;
    static const int COMMON_MSG_INT_RESPONSE = 1337;

    class DummyRequestHandler: public SIMUCOPTER::AbstractBridgeRequestHandler {
    public:
        void handle(const BridgeMessage& msg, BridgeMessage& response) {
            int tmp = COMMON_MSG_INT_RESPONSE;
            response.set_data(&tmp, sizeof(tmp));
        };
    };

    class DummyCommandHandler: public SIMUCOPTER::AbstractBridgeCommandHandler {
    public:
        int last_id = -1;
        double last_arg1 = -1.0;
        double last_arg2 = -1.0;

        void handle(const BridgeMessage& msg) {
            struct {
                double arg1;
                double arg2;
            } arg_s;
            arg_s.arg1 = -1.0;
            arg_s.arg2 = -1.0;

            last_id = msg.id;
            msg.load_data(&arg_s, sizeof(arg_s));
            last_arg1 = arg_s.arg1;
            last_arg2 = arg_s.arg2;
        }
    };

    class TestIntBridgeClientAndService: public testing::Test {
    public:
        std::string current_req_url;
        std::string current_cmd_url;
        BridgeMessage msg;
        TestIntBridgeClientAndService() :
                msg(BridgeMessageType::REQUEST, COMMON_MSG_ID)
        {
        }

    protected:
        virtual void SetUp() {
            current_req_url = get_random_zmq_url();
            current_cmd_url = get_random_zmq_url();
        }
    };

    void run_service(BridgeService* service) {
        printf("Thread start!\n");
        while(!service->update());
    }
}


TEST_F(TestIntBridgeClientAndService, NotInitializedByDefault) {
    BridgeClient client(current_req_url, current_cmd_url);
    BridgeService service(current_req_url, current_cmd_url);
    ASSERT_FALSE(client.is_initialized());
    ASSERT_FALSE(service.is_initialized());
}

TEST_F(TestIntBridgeClientAndService, InitBothSides) {
    BridgeClient client(current_req_url, current_cmd_url);
    BridgeService service(current_req_url, current_cmd_url);
    ASSERT_FALSE(client.is_initialized()) << "Pre-condition failed: BridgeClient is already initialized!";
    ASSERT_FALSE(service.is_initialized()) << "Pre-condition failed: BridgeService is already initialized!";
    service.init();
    client.init();
    ASSERT_TRUE(service.is_initialized());
    ASSERT_TRUE(client.is_initialized());
    service.close();
    client.close();
}

TEST_F(TestIntBridgeClientAndService, RequestChannelWorks) {
    BridgeClient client(current_req_url, current_cmd_url);
    BridgeService service(current_req_url, current_cmd_url);
    DummyRequestHandler handler;

    client.init();
    service.init();
    service.set_request_handler(COMMON_MSG_ID, &handler);

    // we need to run an update() in another thread because
    // client.request_int() is going to block until a response comes in
    std::thread service_thread(run_service, &service);
    ASSERT_EQ(COMMON_MSG_INT_RESPONSE, client.request_int(COMMON_MSG_ID));
    service_thread.join();

    service.close();
    client.close();
}

TEST_F(TestIntBridgeClientAndService, RequestChannelWithUnassignedMsgIdReturnsZero) {
    BridgeClient client(current_req_url, current_cmd_url);
    BridgeService service(current_req_url, current_cmd_url);
    DummyRequestHandler handler;

    client.init();
    service.init();
    service.set_request_handler(COMMON_MSG_ID, &handler);

    // we need to run an update() in another thread because
    // client.request_int() is going to block until a response comes in
    std::thread service_thread(run_service, &service);
    ASSERT_EQ(0, client.request_int(0x1337));
    service_thread.join();

    service.close();
    client.close();
}

TEST_F(TestIntBridgeClientAndService, CommandChannelPassesAllMessages) {
    BridgeService service(current_req_url, current_cmd_url);
    BridgeClient client(current_req_url, current_cmd_url);
    DummyCommandHandler handler;

    service.init();
    client.init();
    handler.init();

    /**************************************************************************
     * NOTE: FOR SOME REASON, DOING A service.update() LOOP HERE WOULD PREVENT
     *       THE MESSAGES FROM BEING DELIVERED!
     *
     *       IT'S POSSIBLE THAT THE INNER WORKINGS OF ZMQ DON'T SUPPORT THIS!
     */
    std::thread t(run_service, &service);

    usleep(500000);
    ASSERT_TRUE(client.send_command(0x1000));
    ASSERT_TRUE(client.send_command(0x1001, 0.01));
    ASSERT_TRUE(client.send_command(0x1002, 0.02, 0.03));

    t.join();

    ASSERT_TRUE(handler.handle_next());
    ASSERT_EQ(0x1000, handler.last_id);
    ASSERT_TRUE(handler.handle_next());
    ASSERT_EQ(0x1001, handler.last_id);
    ASSERT_EQ(0.01, handler.last_arg1);
    ASSERT_TRUE(handler.handle_next());
    ASSERT_EQ(0x1002, handler.last_id);
    ASSERT_EQ(0.02, handler.last_arg1);
    ASSERT_EQ(0.03, handler.last_arg2);
    ASSERT_FALSE(handler.handle_next());
}
