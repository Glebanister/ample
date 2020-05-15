#include <imgui.h>

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

void ActionGui::onEdit()
{
    ImGui::InputText("Attach object", attachedObjectName, 255);
}

void ActionGui::onSubmitEdit()
{
    if (attachedObjectName[0])
    {
        if (!_baseActionPointer->getNamespace().getObject(attachedObjectName))
        {
            throw game::GameException("Could not find object in namespace with name" + static_cast<std::string>(attachedObjectName));
        }
        _baseActionPointer->addObjectName(attachedObjectName);
    }
}

std::shared_ptr<game::Action> ActionGui::getAction()
{
    return _baseActionPointer;
}
} // namespace ample::gui
