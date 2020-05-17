#include <imgui.h>

#include "ObjectStorageGui.h"
#include "Utils.h"
#include "objects/ActionGui.h"

namespace ample::gui
{
ActionGui::ActionGui(std::shared_ptr<filing::NamedObject> action, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor), _objectStorageGui(storage), _baseActionPointer(std::dynamic_pointer_cast<game::Action>(action))
{
}

ActionGui::ActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

void ActionGui::setState(std::shared_ptr<game::StateMachine::State> state) noexcept
{
    _state = state;
}

std::shared_ptr<game::StateMachine::State> ActionGui::getState() const noexcept
{
    return _state;
}

std::shared_ptr<game::Action> ActionGui::getAction()
{
    return _baseActionPointer;
}
} // namespace ample::gui
