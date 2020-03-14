cmake_minimum_required(VERSION 3.3)

project(AmpleGUI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -fPIC")

set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_INCLUDE_DIRS /usr/include/SDL2/)

include_directories(include)
include_directories(../extern/imgui/)
include_directories(../extern/imgui_sdl/)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(../core/include)

set(IMGUI_SOURCES
    ../extern/imgui/imgui.cpp
    ../extern/imgui/imgui_draw.cpp
    ../extern/imgui/imgui_demo.cpp
    ../extern/imgui/imgui_widgets.cpp
    ../extern/imgui_sdl/imgui_sdl.cpp
   )

set(SOURCES
    src/main.cpp)

add_executable(AmpleGUI ${SOURCES} ${IMGUI_SOURCES})

target_link_libraries(AmpleGUI ${SDL2_LIBRARY})
target_link_libraries(AmpleGUI Ample)
