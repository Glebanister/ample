#include <imgui.h>

#include "objects/ActionGui.h"
#include "Utils.h"

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

void ActionGui::onEdit()
{
    gui_utils::NamedObjectSelector("Add object to action", _selectedObjectToAdd, _baseActionPointer->getNamespacePointer()->getAllNames());
}

void ActionGui::onSubmitEdit()
{
    _baseActionPointer->addObjectName(_selectedObjectToAdd->name());
}

std::shared_ptr<game::Action> ActionGui::getAction()
{
    return _baseActionPointer;
}
} // namespace ample::gui
