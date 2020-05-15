#include <imgui.h>
#include <imnodes.h>

#include "Utils.h"
#include "objects/KeyboardTransitionGui.h"

namespace ample::gui
{
std::unordered_map<std::string, game::KeyboardTransition::type> typeIdByName{
    {"down", game::KeyboardTransition::type::DOWN},
    {"not down", game::KeyboardTransition::type::NOT_DOWN},
    {"pressed", game::KeyboardTransition::type::PRESSED},
    {"released", game::KeyboardTransition::type::RELEASED},
};

std::unordered_map<game::KeyboardTransition::type, std::string> typeNameById{
    {game::KeyboardTransition::type::DOWN, "down"},
    {game::KeyboardTransition::type::NOT_DOWN, "not down"},
    {game::KeyboardTransition::type::PRESSED, "pressed"},
    {game::KeyboardTransition::type::RELEASED, "released"},
};

KeyboardTransitionGui::KeyboardTransitionGui(std::shared_ptr<filing::NamedObject> sm, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(sm, editor, storage),
      _transition(std::dynamic_pointer_cast<game::KeyboardTransition>(sm))
{
    pressType = _transition->getPressType();
    key = _transition->getKey();
    pressTypeString = typeNameById[pressType];
}

KeyboardTransitionGui::KeyboardTransitionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : TransitionGui(editor, storage)
{
}

void KeyboardTransitionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    TransitionGui::onCreate();
    gui_utils::StringSelector("Press type", pressTypeString, {"down", "not down", "pressed", "released"});
    gui_utils::inputKeysym("Trigger key", key);
}

void KeyboardTransitionGui::onSubmitCreate()
{
    if (!_nextState)
    {
        throw game::GameException("Next state is not set");
    }
    pressType = typeIdByName[pressTypeString];
    _transition = std::make_shared<game::KeyboardTransition>(nameBuffer, _nextState, pressType, key);
    _baseTransition = _transition;
}

void KeyboardTransitionGui::onEdit()
{
    ASSERT(_transition);
    gui_utils::StringSelector("Press type", pressTypeString, {"down", "not down", "pressed", "released"});
    gui_utils::inputKeysym("Trigger key", key);
}

void KeyboardTransitionGui::onSubmitEdit()
{
    _transition->setPressType(typeIdByName[pressTypeString]);
    _transition->setKey(key);
}

void KeyboardTransitionGui::onView()
{
    TransitionGui::onView();
}

void KeyboardTransitionGui::onInspect()
{
}

void KeyboardTransitionGui::onPreview()
{
    ImGui::Text("Key: %d", static_cast<int>(key));
    ImGui::Text("Press type: %s", pressTypeString.c_str());
}

std::string KeyboardTransitionGui::name() const
{
    ASSERT(_transition);
    return _transition->name();
}
std::string KeyboardTransitionGui::className() const
{
    return "KeyboardTransition";
}
} // namespace ample::gui
