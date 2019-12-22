cmake_minimum_required(VERSION 3.0)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

find_package(SDL2 REQUIRED)

set(DRAW_SOURCES Draw/src/*.cpp)

file(GLOB AMPLE_SOURCES . ${DRAW_SOURCES})
include_directories(Draw/include)
set(SOURCE_LIB ${AMPLE_SOURCES})
add_library(Ample SHARED ${SOURCE_LIB})
