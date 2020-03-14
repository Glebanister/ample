cmake_minimum_required(VERSION 3.3)

project(ample)

include_directories(${CMAKE_PROJECT_NAME}/include)

add_subdirectory(core)
add_subdirectory(gui)
