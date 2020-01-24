cmake_minimum_required(VERSION 3.3)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -fPIC")

set(OPENGL_gl_LIBRARY /usr/lib/x86_64-linux-gnu/libGL.so)
set(OPENGL_INCLUDE_DIRS /usr/include/GL/)

set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_INCLUDE_DIRS /usr/include/SDL2/)

set(GLU_LIBRARY /usr/lib/x86_64-linux-gnu/libGLU.so)


set(AMPLE_SOURCES

    src/Basic/Activity.cpp
    src/Basic/Storage.cpp

    src/Control/EventManager.cpp
    src/Control/EventHandler.cpp
    
    src/Os/Window.cpp
    src/Os/OsManager.cpp
    src/Os/Clock.cpp
    src/Os/Error.cpp

    src/Graphics/LayeredWindowActivity.cpp
    src/Graphics/WindowObject.cpp
    src/Graphics/Colors.cpp

    src/Geometry/Vector.cpp

    src/Utils/Utils.cpp
    )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(lib/googletest)
add_subdirectory(test)

include_directories(include)

set(SOURCE_LIB ${AMPLE_SOURCES})

add_library(Ample SHARED ${SOURCE_LIB})

target_link_libraries(Ample ${SDL2_LIBRARY})
target_link_libraries(Ample ${OPENGL_gl_LIBRARY})
target_link_libraries(Ample ${GLU_LIBRARY})
