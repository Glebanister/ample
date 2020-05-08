#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "ample/Level.h"
#include "ample/NamedObject.h"
#include "ample/Singleton.h"
#include "ample/Game2dEditor.h"

#include "Utils.h"
#include "objects/ObjectGui.h"

namespace ample::gui
{
class ObjectGui;   
} // namespace ample::gui


namespace ample::gui
{
enum class finalObjectClass
{
    LEVEL,
    // SLICE,
    // GRAPHICAL_OBJECT,
    // GRAPHICAL_POLYGON,
    // GRAPHICAL_EDGE,
    // GRAPHICAL_OBJECT_2D,
    WORLD_OBJECT_2D,
    STATE_MACHINE,
};

static std::unordered_map<std::string, finalObjectClass> classIdByClassName{
    {"Level", finalObjectClass::LEVEL},
    // {"Scene2d", finalObjectClass::SLICE},
    // {"GraphicalObject", finalObjectClass::GRAPHICAL_OBJECT},
    // {"GraphicalPolygon", finalObjectClass::GRAPHICAL_POLYGON},
    // {"GraphicalEdge", finalObjectClass::GRAPHICAL_EDGE},
    // {"GraphicalObject2d", finalObjectClass::GRAPHICAL_OBJECT_2D},
    {"WorldObject2d", finalObjectClass::WORLD_OBJECT_2D},
    {"StateMachine", finalObjectClass::STATE_MACHINE},
};

class ObjectStorageGui
{
public:
    ObjectStorageGui(std::shared_ptr<game::game2d::Game2dEditor>);

    template <typename... Args>
    void create(finalObjectClass, Args... args);
    void cancelCreate();

    void browser();
    void editor();
    void creator();
    void inspector();
    void viewer();

    std::shared_ptr<ObjectGui> objectGuiByName(const std::string &name);

    void setFocus(std::shared_ptr<ObjectGui> gui);  

    void inspectSingleItem(const std::string &name);
    void inspectSingleItem(std::shared_ptr<ObjectGui>);

private:
    template <typename... Args>
    std::unique_ptr<ObjectGui> buildGui(finalObjectClass, Args... args);
    template <class T>
    void buildGuiAndAdd(std::shared_ptr<T>);

    std::shared_ptr<ObjectGui> _onInput; // always no more than one
    std::unordered_map<std::string, std::shared_ptr<ObjectGui>> _guiByObjectName;
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    std::shared_ptr<ObjectGui> _focusedGui;

    bool _creationSuccess = false;
    gui_utils::MessagePopup _creationFailPopup;
    gui_utils::MessagePopup _editionFailPopup;
};
} // namespace ample::gui

#include "templates/ObjectStorageGui.hpp"
