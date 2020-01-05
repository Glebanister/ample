cmake_minimum_required(VERSION 3.0)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

set(BASIS_SOURCES
Basis/src/Storage.cpp
Basis/src/Condition.cpp
Basis/src/Activity.cpp
    )
file(GLOB AMPLE_SOURCES . ${BASIS_SOURCES})
include_directories(Basis/include)
set(SOURCE_LIB ${AMPLE_SOURCES})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")
add_library(Ample SHARED ${SOURCE_LIB})
