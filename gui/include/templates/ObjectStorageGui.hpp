#pragma once

#include "ample/GraphicalPolygon.h"
#include "ample/Level.h"
#include "ample/StateMachine.h"

#include "objects/ActionGui.h"
#include "objects/GraphicalEdgeGui.h"
#include "objects/GraphicalObject2dGui.h"
#include "objects/GraphicalObjectGui.h"
#include "objects/GraphicalPolygonGui.h"
#include "objects/GraphicalRotateActionGui.h"
#include "objects/LevelGui.h"
#include "objects/SliceGui.h"
#include "objects/StateGui.h"
#include "objects/StateMachineGui.h"
#include "objects/TextureGui.h"
#include "objects/TimerTransitionGui.h"
#include "objects/KeyboardTransitionGui.h"
#include "objects/WorldObjectGui.h"
#include "objects/PhysicalApplyForceActionGui.h"
#include "objects/FollowObjectActionGui.h"
#include "objects/CameraTranslateActionGui.h"

namespace ample::gui
{
class GraphicalEdgeGui;
class GraphicalObject2dGui;
class GraphicalObjectGui;
class GraphicalPolygonGui;
class LevelGui;
class SliceGui;
class StateMachineGui;
class WorldObjectGui;
class TextureGui;
class TimerTransitionGui;
class GraphicalRotateActionGui;
class StateGui;
class ActionGui;
class KeyboardTransitionGui;
class PhysicalApplyForceActionGui;
class FollowObjectActionGui;
class CameraTranslateActionGui;
} // namespace ample::gui

namespace ample::gui
{
template <typename... Args>
inline std::unique_ptr<ObjectGui> ObjectStorageGui::buildGui(finalObjectClass objClass, Args... args)
{
    std::unique_ptr<ObjectGui> result;
    switch (objClass)
    {
    case finalObjectClass::LEVEL:
        result = std::make_unique<LevelGui>(args...);
        break;
    case finalObjectClass::SLICE:
        result = std::make_unique<SliceGui>(args...);
        break;
    case finalObjectClass::STATE_MACHINE:
        result = std::make_unique<StateMachineGui>(args...);
        break;
    case finalObjectClass::STATE:
        result = std::make_unique<StateGui>(args...);
        break;
    case finalObjectClass::WORLD_OBJECT_2D:
        result = std::make_unique<WorldObjectGui>(args...);
        break;
    case finalObjectClass::TEXTURE:
        result = std::make_unique<TextureGui>(args...);
        break;
    case finalObjectClass::TIMER_TRANSITION:
        result = std::make_unique<TimerTransitionGui>(args...);
        break;
    case finalObjectClass::KEYBOARD_TRANSITION:
        result = std::make_unique<KeyboardTransitionGui>(args...);
        break;
    case finalObjectClass::GRAPHICAL_ROTATE_ACTION:
        result = std::make_unique<GraphicalRotateActionGui>(args...);
        break;
    case finalObjectClass::PHYSICAL_APPLY_FORCE_ACTION:
        result = std::make_unique<PhysicalApplyForceActionGui>(args...);
        break;
    case finalObjectClass::FOLLOW_OBJECT_ACTION:
        result = std::make_unique<FollowObjectActionGui>(args...);
        break;
    case finalObjectClass::CAMERA_TRANSLATE_ACTION:
        result = std::make_unique<CameraTranslateActionGui>(args...);
        break;
    default:
        ASSERT(false);
    }
    return result;
}

template <class T>
std::shared_ptr<ObjectGui> ObjectStorageGui::buildGuiAndAdd(std::shared_ptr<T> object)
{
    ASSERT(classIdByClassName.find(object->className()) != classIdByClassName.end());
    std::shared_ptr<ObjectGui> objectGui = buildGui(classIdByClassName[object->className()].finalClass, object, _game2dEditor, this);
    _guiByObjectName[object->name()] = objectGui;
    return objectGui;
}
} // namespace ample::gui
