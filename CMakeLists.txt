cmake_minimum_required(VERSION 3.0)

project(TestAmple)

set(SOURCE_EXE src/main.cpp)
add_executable(main ${SOURCE_EXE})

include_directories(Ample/Draw/include)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(Ample)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_link_libraries(main Ample)
target_link_libraries(main ${SDL2_LIBRARIES})
