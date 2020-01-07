cmake_minimum_required(VERSION 3.0)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

find_package(SDL2 REQUIRED)

set(AMPLE_SOURCES

    src/Ample/Storage.cpp
    src/Ample/LogicBlock.cpp
    src/Ample/Activity.cpp

    src/Control/EventManager.cpp
    src/Control/EventHandler.cpp

    src/Window/Window.cpp
    src/Window/WindowActivity.cpp
    )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(include)

set(SOURCE_LIB ${AMPLE_SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

add_library(Ample SHARED ${SOURCE_LIB})
target_link_libraries(Ample ${SDL2_LIBRARIES})
