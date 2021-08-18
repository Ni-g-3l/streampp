cmake_minimum_required(VERSION 3.19)
project(streampp)

set(CMAKE_CXX_STANDARD 14)

include_directories(./inc)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE inc/)

add_executable(streampp-test src/main.cpp)
