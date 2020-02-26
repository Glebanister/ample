cmake_minimum_required(VERSION 3.5)

project(DemoGame)
set(APP_NAME DemoGame)

set(SOURCES
    src/main.cpp
    src/DemoGame.cpp
    src/SquareBehavior.cpp
    src/CameraBehavior.cpp)

find_library(AMPLE_LIBRARY NAME Ample
                           PATHS ../build/Ample)
find_path(AMPLE_INCLUDE_DIR NAMES Activity.h
                            PATHS ../Ample/include)

message(INFO " ample library found in ${AMPLE_LIBRARY}")
message(INFO " ample headers found in ${AMPLE_INCLUDE_DIR}")
message(INFO " sources list: ${SOURCES}")

add_executable(${APP_NAME} ${SOURCES})

include_directories(include)
include_directories(${AMPLE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")

target_link_libraries(${APP_NAME} ${AMPLE_LIBRARY})
