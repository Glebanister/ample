cmake_minimum_required(VERSION 3.0)

project(WhatIsAmple)

set(APP_NAME what_is_ample)

set(SOURCE_EXE src/test.cpp)
add_executable(${APP_NAME} ${SOURCE_EXE})

include_directories(Ample/include)

add_subdirectory(Ample)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++17")

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} Ample ${GLUT_LIBRARY})
