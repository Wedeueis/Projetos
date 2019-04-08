cmake_minimum_required (VERSION 2.6)

project (vssvision)

find_package( OpenCV REQUIRED )
find_package( Jsoncpp REQUIRED )

include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${JSONCPP_INCLUDE_DIR})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_subdirectory(exes)
