cmake_minimum_required(VERSION 3.0)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

find_package(SDL2 REQUIRED)

set(AMPLE_SOURCES

    Ample/src/Storage.cpp
    Ample/src/Condition.cpp
    Ample/src/Activity.cpp

    Control/src/EventManager.cpp
    Control/src/EventHandler.cpp
    )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(Ample/include/)
include_directories(Control/include/)

set(SOURCE_LIB ${AMPLE_SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

add_library(Ample SHARED ${SOURCE_LIB})
target_link_libraries(Ample ${SDL2_LIBRARIES})
