#pragma once

#include "ample/GraphicalPolygon.h"
#include "ample/Level.h"
#include "ample/StateMachine.h"

#include "objects/GraphicalEdgeGui.h"
#include "objects/GraphicalObject2dGui.h"
#include "objects/GraphicalObjectGui.h"
#include "objects/GraphicalPolygonGui.h"
#include "objects/LevelGui.h"
#include "objects/SliceGui.h"
#include "objects/StateMachineGui.h"
#include "objects/WorldObjectGui.h"

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
} // namespace ample::gui

namespace ample::gui
{
template <typename... Args>
inline std::unique_ptr<ObjectGui> ObjectStorageGui::buildGui(finalObjectClass objClass, Args... args)
{
    std::unique_ptr<ObjectGui> result;
    switch (objClass)
    {
    // case finalObjectClass::GRAPHICAL_EDGE:
    //     result = std::make_unique<GraphicalEdgeGui>(args...);
    //     break;
    // case finalObjectClass::GRAPHICAL_OBJECT_2D:
    //     result = std::make_unique<GraphicalObject2dGui>(args...);
    //     break;
    // case finalObjectClass::GRAPHICAL_OBJECT:
    //     result = std::make_unique<GraphicalObjectGui>(args...);
    //     break;
    // case finalObjectClass::GRAPHICAL_POLYGON:
    //     result = std::make_unique<GraphicalPolygonGui>(args...);
    //     break;
    case finalObjectClass::LEVEL:
        result = std::make_unique<LevelGui>(args...);
        break;
    case finalObjectClass::SLICE:
        result = std::make_unique<SliceGui>(args...);
        break;
    // case finalObjectClass::STATE_MACHINE:
    //     result = std::make_unique<StateMachineGui>(args...);
    //     break;
    // case finalObjectClass::WORLD_OBJECT:
    //     result = std::make_unique<WorldObjectGui>(args...);
    //     break;
    // case finalObjectClass::SLICE:
    //     result = std::make_unique<SliceGui>(args...);
    //     break;
    case finalObjectClass::STATE_MACHINE:
        result = std::make_unique<StateMachineGui>(args...);
        break;
    case finalObjectClass::WORLD_OBJECT_2D:
        result = std::make_unique<WorldObjectGui>(args...);
        break;
    }

    return result;
}

template <typename... Args>
inline void ObjectStorageGui::create(finalObjectClass objClass, Args... args)
{
    ASSERT(!_onInput);
    _onInput = buildGui(objClass, args...); // TODO: std::forward
}

template <class T>
void ObjectStorageGui::buildGuiAndAdd(std::shared_ptr<T> object)
{
    ASSERT(classIdByClassName.find(object->className()) != classIdByClassName.end());
    std::shared_ptr<ObjectGui> objectGui = buildGui(classIdByClassName[object->className()], object, _game2dEditor, this);
    _guiByObjectName.emplace(object->name(), objectGui);
}
} // namespace ample::gui
