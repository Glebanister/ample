cmake_minimum_required(VERSION 3.0)

project(TestAmple)

set(APP_NAME test_ample)

set(SOURCE_EXE src/test.cpp)
add_executable(${APP_NAME} ${SOURCE_EXE})

include_directories(Ample/include)

add_subdirectory(Ample)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++17")

target_link_libraries(${APP_NAME} Ample)
