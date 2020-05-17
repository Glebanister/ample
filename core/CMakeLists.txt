cmake_minimum_required(VERSION 3.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++17 -fPIC")

set(OPENGL_gl_LIBRARY /usr/lib/x86_64-linux-gnu/libGL.so)
set(OPENGL_INCLUDE_DIRS /usr/include/GL/)

set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
set(SDL2_INCLUDE_DIRS /usr/include/SDL2/)

set(GLM_INCLUDE_DIRS /usr/include/glm/)

set(GLU_LIBRARY /usr/lib/x86_64-linux-gnu/libGLU.so)

set(IL_LIBRARY /usr/lib/x86_64-linux-gnu/libIL.so)
set(ILU_LIBRARY /usr/lib/x86_64-linux-gnu/libILU.so)
set(ILUT_LIBRARY /usr/lib/x86_64-linux-gnu/libILUT.so)
set(IL_INCLUDE_DIRS /usr/include/IL/)

set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Build the Box2D unit tests")
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Build the Box2D testbed")
add_subdirectory(../extern/box2d buildBox2d)

set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "Build rapidjson documentation.")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Build rapidjson examples.")
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Build rapidjson perftests and unittests.")
add_subdirectory(../extern/rapidjson buildRapidjson)

include_directories(../extern/box2d/include)
include_directories(../extern/rapidjson/include)

set(${CMAKE_PROJECT_NAME}_SOURCES

    src/Basic/Activity.cpp
    src/Basic/Behaviour.cpp

    src/Control/EventManager.cpp
    src/Control/EventHandler.cpp
    
    src/Os/WindowActivity.cpp
    src/Os/Clock.cpp
    src/Os/Exception.cpp
    src/Os/Window.cpp
    src/Os/OpenGLEnvironment.cpp
    src/Os/SDLEnvironment.cpp
    src/Os/ILEnvironment.cpp

    src/Utils/Utils.cpp
    src/Utils/Singleton.cpp
    src/Utils/Noncopyable.cpp

    src/Filing/Scene2d.cpp
    src/Filing/NamedObject.cpp
    src/Filing/StoredObject.cpp
    src/Filing/NamedStoredObject.cpp

    src/Graphics/GraphicalObject.cpp
    src/Graphics/GraphicalObject2d.cpp
    src/Graphics/Camera.cpp
    src/Graphics/Color.cpp
    src/Graphics/CameraPerspective.cpp
    src/Graphics/CameraOrtho.cpp
    src/Graphics/Layer.cpp
    src/Graphics/LayeredWindowActivity.cpp
    src/Graphics/VertexArray.cpp
    src/Graphics/Shaders/Shader.cpp
    src/Graphics/Shaders/ShaderProcessor.cpp
    src/Graphics/Light/LightSource.cpp
    src/Graphics/Texture.cpp
    src/Graphics/GraphicalEdge.cpp
    src/Graphics/GraphicalPolygon.cpp

    src/Physics/ContactListener.cpp
    src/Physics/WorldObject2d.cpp
    src/Physics/WorldLayer2d.cpp
    src/Physics/WorldJoint2d.cpp
    src/Physics/WorldDistanceJoint.cpp
    src/Physics/WorldRevoluteJoint2d.cpp
    src/Physics/WorldPrismaticJoint2d.cpp
    src/Physics/WorldPulleyJoint2d.cpp
    src/Physics/WorldGearJoint2d.cpp
    src/Physics/WorldMouseJoint2d.cpp
    src/Physics/WorldWheelJoint2d.cpp
    src/Physics/WorldWeldJoint2d.cpp
    src/Physics/WorldRopeJoint2d.cpp
    src/Physics/WorldFrictionJoint2d.cpp
    src/Physics/WorldMotorJoint2d.cpp
    src/Physics/WorldContact2d.cpp

    src/Geometry/RegularPolygon.cpp
    src/Geometry/VectorRectangle.cpp
    src/Geometry/Shape.cpp
    src/Geometry/Rectangle.cpp
    src/Geometry/Circle.cpp
    src/Geometry/Point.cpp

    src/Game/Game2d/Game2d.cpp
    src/Game/Game2d/Game2dEditor.cpp
    src/Game/Game2d/Level.cpp
    src/Game/GameException.cpp
    src/Game/StateMachine/StateMachine.cpp
    src/Game/StateMachine/Transitions/Os/EnvironmentTransition.cpp
    src/Game/StateMachine/Transitions/Os/KeyboardTransition.cpp
    src/Game/StateMachine/Transitions/Os/MouseTransition.cpp
    src/Game/StateMachine/Transitions/Os/TimerTransition.cpp
    src/Game/StateMachine/Transitions/Physics/PhysicalTransition.cpp
    src/Game/StateMachine/Transitions/Physics/DistanceTransition.cpp
    src/Game/StateMachine/Transitions/Physics/CollisionTransition.cpp
    src/Game/StateMachine/Transitions/Physics/SpeedTransition.cpp
    src/Game/StateMachine/Transitions/Physics/PositionTransition.cpp
    src/Game/StateMachine/Transitions/Physics/CollisionTransition.cpp
    src/Game/StateMachine/Actions/Graphical/GraphicalAction.cpp
    src/Game/StateMachine/Actions/Graphical/GraphicalRotateAction.cpp
    src/Game/StateMachine/Actions/Graphical/GraphicalTranslateAction.cpp
    src/Game/StateMachine/Actions/Camera/CameraAction.cpp
    src/Game/StateMachine/Actions/Camera/CameraTranslateAction.cpp
    src/Game/StateMachine/Actions/Camera/FollowObjectAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalLinearVelocityAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalAngularVelocityAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalApplyForceAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalAngularDampingAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalApplyAngularImpAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalApplyLinearImpAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalApplyTorqueAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalFixRotationAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalGravityScaleAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalLinearDampingAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalSetAwakeAction.cpp
    src/Game/StateMachine/Actions/Physical/PhysicalSetEnabledAction.cpp
    src/Game/StateMachine/Action.cpp
    src/Game/Events/EventListener.cpp
    src/Game/Namespace.cpp
    src/Game/LevelSwitcher.cpp
    src/Game/LevelLoader.cpp
   )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${IL_INCLUDE_DIRS})

include_directories(include/ample)

set(SOURCE_LIB ${${CMAKE_PROJECT_NAME}_SOURCES})

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE_LIB})

target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GLU_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${IL_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${ILU_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} ${ILUT_LIBRARY})
target_link_libraries(${CMAKE_PROJECT_NAME} box2d)
