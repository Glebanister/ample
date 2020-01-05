cmake_minimum_required(VERSION 3.0)

project(TestAmple)

set(SOURCE_EXE src/main.cpp)
add_executable(test_ample ${SOURCE_EXE})

include_directories(Ample/Basis/include)

add_subdirectory(Ample)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_link_libraries(test_ample Ample)
