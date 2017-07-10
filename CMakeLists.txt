cmake_minimum_required(VERSION 3.7)
project(bridge)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest
add_subdirectory(bridge_test/lib/googletest)
include_directories(bridge_test/lib/googletest/googletest/include)
include_directories(bridge_test/lib/googletest/googlemock/include)

# bridge library
include_directories(.)

set(SOURCE_FILES_BRIDGE
        main.cpp
        bridge/simucopter-bridge.h
        bridge/AbstractBridgeCommandHandler.cpp bridge/AbstractBridgeCommandHandler.h bridge_test/TestUnitAbstractBridgeCommandHandler.cpp
        bridge/BridgeClient.cpp  bridge/BridgeClient.h  bridge_test/TestUnitBridgeClient.cpp
        bridge/BridgeMessage.cpp bridge/BridgeMessage.h bridge_test/TestUnitBridgeMessage.cpp
        bridge/BridgeService.cpp bridge/BridgeService.h bridge_test/TestUnitBridgeService.cpp
        bridge/ZmqBridgeMessageSerializer.cpp bridge/ZmqBridgeMessageSerializer.h bridge_test/TestUnitZmqMessageSerializer.cpp
        bridge/ArgumentPacker.cpp bridge/ArgumentPacker.h bridge_test/TestUnitArgumentPacker.cpp
        bridge_test/test-common.h
        bridge_test/TestIntBridgeClientAndService.cpp)

# simucopter source
# TODO: Some of these sources can't be compiled locally without ArduPilot code - deal with it somehow
#set(SOURCE_FILES_SIMUCOPTER
#        main.cpp
#        simucopter/SimuCopterMessage.h simucopter/SimulinkBridgeInterface.h simucopter/ArduCopterRequestHandler.cpp simucopter/ArduCopterRequestHandler.h simucopter/ArduCopterCommandHandler.cpp simucopter/ArduCopterCommandHandler.h simucopter/simucopter-arducopter.h simucopter/simucopter-arducopter.cpp simucopter/control_simulink.cpp)

add_executable(test_bridge ${SOURCE_FILES_BRIDGE})
#add_executable(test_simucopter ${SOURCE_FILES_SIMUCOPTER})

target_link_libraries(test_bridge zmq gtest gtest_main)