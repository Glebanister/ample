cmake_minimum_required(VERSION 3.5)

project(demo)
set(APP_NAME demo)

set(SOURCES
    src/main.cpp
    src/DemoGame.cpp
    src/SquareBehavior.cpp
    src/CameraBehavior.cpp)

find_library(AMPLE_LIBRARY NAME ample
                           PATHS ../build/core/)
find_path(AMPLE_INCLUDE_DIR NAMES Activity.h
                            PATHS ../core/include/ample)

message(INFO " ample library found in ${AMPLE_LIBRARY}")
message(INFO " ample headers found in ${AMPLE_INCLUDE_DIR}")
message(INFO " sources list: ${SOURCES}")

add_executable(${APP_NAME} ${SOURCES})

include_directories(include)
include_directories(../extern/box2d/include)
include_directories(../extern/rapidjson/include)
include_directories(${AMPLE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

target_link_libraries(${APP_NAME} ${AMPLE_LIBRARY})
