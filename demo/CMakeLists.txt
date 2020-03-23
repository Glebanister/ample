cmake_minimum_required(VERSION 3.5)

project(demo)
set(APP_NAME demo)

set(SOURCES
    src/main.cpp
    src/DemoGame.cpp
    src/CameraRemoter.cpp)

add_executable(${APP_NAME} ${SOURCES})

include_directories(include)
include_directories(../extern/box2d/include)
include_directories(../extern/rapidjson/include)
include_directories(../core/include/ample/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

target_link_libraries(${APP_NAME} ample)
