cmake_minimum_required(VERSION 3.19)
project(streampp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)