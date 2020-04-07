cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_COMPILER /usr/bin/g++-9)

project(ample)

include_directories(${CMAKE_PROJECT_NAME}/include)

add_subdirectory(core)
add_subdirectory(gui)
add_subdirectory(demo)
