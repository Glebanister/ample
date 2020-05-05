cmake_minimum_required(VERSION 3.5)

project(ample-engine)

set(SOURCES
    src/main.cpp)

add_executable(ample-engine ${SOURCES})

add_subdirectory(../extern/cxxopts build_cxxopts)

set(CXXOPTS_BUILD_EXAMPLES OFF BOOL)
set(CXXOPTS_BUILD_TESTS OFF BOOL)
set(CXXOPTS_ENABLE_INSTALL OFF BOOL)

include_directories(include)
include_directories(../extern/box2d/include)
include_directories(../extern/rapidjson/include)
include_directories(../extern/cxxopts/include)
include_directories(../core/include/ample/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

target_link_libraries(ample-engine ample)
target_link_libraries(ample-engine cxxopts)
