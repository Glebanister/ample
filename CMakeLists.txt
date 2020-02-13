cmake_minimum_required(VERSION 3.3)

project(Ample)

include_directories(${CMAKE_PROJECT_NAME}/include)
include_directories(${CMAKE_PROJECT_NAME}/googletest/include)

add_subdirectory(lib/googletest)
add_subdirectory(${CMAKE_PROJECT_NAME})
add_subdirectory(test)
