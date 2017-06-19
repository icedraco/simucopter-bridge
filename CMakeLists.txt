cmake_minimum_required(VERSION 3.7)
project(simucopter)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest
add_subdirectory(bridge_test/lib/googletest)
include_directories(bridge_test/lib/googletest/googletest/include)
include_directories(bridge_test/lib/googletest/googlemock/include)

# simucopter library
include_directories(simucopter)

set(SOURCE_FILES main.cpp simucopter/BridgeMessage.cpp bridge_test/TestUnitBridgeMessage.cpp simucopter/BridgeService.cpp simucopter/BridgeService.h simucopter/AbstractBridgeRequestHandler.h bridge_test/TestUnitBridgeService.cpp simucopter/ZmqBridgeMessageSerializer.cpp simucopter/ZmqBridgeMessageSerializer.h bridge_test/TestUnitZmqMessageSerializer.cpp simucopter/BridgeClient.cpp simucopter/BridgeClient.cpp simucopter/BridgeClient.h bridge_test/TestUnitBridgeClient.cpp bridge_test/TestIntBridgeClientAndService.cpp simucopter/simucopter.h simucopter/AbstractBridgeCommandHandler.cpp simucopter/AbstractBridgeCommandHandler.h bridge_test/TestUnitAbstractBridgeCommandHandler.cpp bridge_test/test-common.h)
add_executable(simutest ${SOURCE_FILES})

target_link_libraries(simutest zmq gtest gtest_main)