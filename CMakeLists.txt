cmake_minimum_required(VERSION 3.0)

project(TestAmple)

set(APP_NAME test_ample)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_EXE src/main.cpp)
add_executable(${APP_NAME} ${SOURCE_EXE})

include_directories(Ample/Basis/include)

add_subdirectory(Ample)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_link_libraries(${APP_NAME} Ample)
target_link_libraries(${APP_NAME} ${SDL2_LIBRARIES})
