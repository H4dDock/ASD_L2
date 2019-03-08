cmake_minimum_required(VERSION 3.13)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(untitled2 main.cpp MyMap.h)
target_link_libraries(untitled2 gtest gtest_main)