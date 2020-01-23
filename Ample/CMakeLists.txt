cmake_minimum_required(VERSION 3.0)

project(Ample VERSION 1.0.0 DESCRIPTION "Ample - the game engine")

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

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
    )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIRS})

add_subdirectory(lib/googletest)
add_subdirectory(test)

include_directories(include)

set(SOURCE_LIB ${AMPLE_SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC")

add_library(Ample SHARED ${SOURCE_LIB})
target_link_libraries(Ample ${SDL2_LIBRARIES})
target_link_libraries(Ample ${OPENGL_gl_LIBRARY})
target_link_libraries(Ample ${OPENGL_glu_LIBRARY})
target_link_libraries(Ample ${glm_LIBRARIES})
