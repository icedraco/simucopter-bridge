cmake_minimum_required(VERSION 3.7)
project(bridge)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest
add_subdirectory(bridge_test/lib/googletest)
include_directories(bridge_test/lib/googletest/googletest/include)
include_directories(bridge_test/lib/googletest/googlemock/include)

# bridge library
include_directories(bridge)

set(SOURCE_FILES
        main.cpp
        bridge/simucopter.h
        bridge/AbstractBridgeCommandHandler.cpp bridge/AbstractBridgeCommandHandler.h bridge_test/TestUnitAbstractBridgeCommandHandler.cpp
        bridge/BridgeClient.cpp  bridge/BridgeClient.h  bridge_test/TestUnitBridgeClient.cpp
        bridge/BridgeMessage.cpp bridge/BridgeMessage.h bridge_test/TestUnitBridgeMessage.cpp
        bridge/BridgeService.cpp bridge/BridgeService.h bridge_test/TestUnitBridgeService.cpp
        bridge/ZmqBridgeMessageSerializer.cpp bridge/ZmqBridgeMessageSerializer.h bridge_test/TestUnitZmqMessageSerializer.cpp
        bridge_test/test-common.h
        bridge_test/TestIntBridgeClientAndService.cpp)

add_executable(simutest ${SOURCE_FILES})

target_link_libraries(simutest zmq gtest gtest_main)