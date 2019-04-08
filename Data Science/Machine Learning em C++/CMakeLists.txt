cmake_minimum_required(VERSION 2.8)

project(machine_learning)

include_directories(${PROJECT_SOURCE_DIR}/inc)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

add_subdirectory(src)