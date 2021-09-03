cmake_minimum_required(VERSION 3.19)
project(streampp-example)

set(CMAKE_CXX_STANDARD 11)

include_directories(../include)

add_executable(${PROJECT_NAME} main.cpp Animal.cpp)