#pragma once

#include <functional>
#include <map>
#include <memory>
#include <unordered_map>

#include "ample/Game2dEditor.h"
#include "ample/Level.h"
#include "ample/NamedObject.h"
#include "ample/Singleton.h"

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
    SLICE,
    WORLD_OBJECT_2D,
    STATE_MACHINE,
    STATE,
    TEXTURE,
    TIMER_TRANSITION,
    GRAPHICAL_ROTATE_ACTION,
};

static std::map<std::string, ClassInfo> classIdByClassName{
    {"Level", {finalObjectClass::LEVEL}},
    {"Scene2d", {finalObjectClass::SLICE}},
    {"WorldObject2d", {finalObjectClass::WORLD_OBJECT_2D}},
    {"StateMachine", {finalObjectClass::STATE_MACHINE}},
    {"State", {finalObjectClass::STATE, false}},
    {"Texture", {finalObjectClass::TEXTURE}},
    {"TimerTransition", {finalObjectClass::TIMER_TRANSITION, false, "Transition"}},
    {"GraphicalRotateAction", {finalObjectClass::GRAPHICAL_ROTATE_ACTION, false, "Action"}},
};

class ObjectStorageGui
{
public:
    ObjectStorageGui(std::shared_ptr<game::game2d::Game2dEditor>);

    template <typename T>
    std::shared_ptr<ObjectGui> buildGuiAndAdd(std::shared_ptr<T>);
    void create(finalObjectClass, bool needsFocus = true, std::function<void(std::shared_ptr<ObjectGui>)> = {});
    void cancelCreate();

    std::shared_ptr<ObjectGui> getOnInputGui() const noexcept;

    void browser();
    void editor();
    void creator();
    void inspector();
    void viewer();
    void texturesViewer();

    std::shared_ptr<ObjectGui> objectGuiByName(const std::string &name);

    void setFocus(std::shared_ptr<ObjectGui> gui);
    void setFocus(std::string guiName);

    void inspectSingleItem(const std::string &name);
    void inspectSingleItem(std::shared_ptr<ObjectGui>);

    std::vector<std::shared_ptr<graphics::Texture>> &texturesList() noexcept;
    std::vector<std::shared_ptr<game::StateMachine::State>> &statesList(const std::string &machineName);

private:
    template <typename... Args>
    std::unique_ptr<ObjectGui> buildGui(finalObjectClass, Args...);

    std::shared_ptr<ObjectGui> _onInput; // always no more than one
    std::function<void(std::shared_ptr<ObjectGui>)> _onInputFunction = {};
    bool _onInputNeedsFocus = true;
    std::unordered_map<std::string, std::shared_ptr<ObjectGui>> _guiByObjectName;
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    std::shared_ptr<ObjectGui> _focusedGui;

    bool _creationSuccess = false;
    gui_utils::MessagePopup _creationFailPopup;
    gui_utils::MessagePopup _editionFailPopup;

    std::vector<std::shared_ptr<graphics::Texture>> _textures;
};
} // namespace ample::gui

#include "templates/ObjectStorageGui.hpp"
