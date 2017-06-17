cmake_minimum_required(VERSION 3.7)
project(simucopter)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest
add_subdirectory(simucopter_test/lib/googletest)
include_directories(simucopter_test/lib/googletest/googletest/include)
include_directories(simucopter_test/lib/googletest/googlemock/include)

# simucopter library
include_directories(simucopter)

set(SOURCE_FILES main.cpp simucopter/BridgeMessage.cpp simucopter_test/TestUnitBridgeMessage.cpp simucopter/BridgeService.cpp simucopter/BridgeService.h simucopter/BridgeRequestHandler.h simucopter_test/TestUnitBridgeService.cpp)
add_executable(simutest ${SOURCE_FILES})

target_link_libraries(simutest zmq gtest gtest_main)