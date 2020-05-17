#include <imgui.h>

#include "ObjectStorageGui.h"
#include "Utils.h"
#include "objects/ObjectGroupActionGui.h"

namespace ample::gui
{
template <typename T>
ObjectGroupActionGui<T>::ObjectGroupActionGui(std::shared_ptr<filing::NamedObject> action,
                                              std::shared_ptr<game::game2d::Game2dEditor> editor,
                                              ObjectStorageGui *storage)
    : ActionGui(action, editor, storage),
      _groupAction(std::dynamic_pointer_cast<game::stateMachine::actions::ObjectGroupAction<T>>(_baseActionPointer))
{
}

template <typename T>
ObjectGroupActionGui<T>::ObjectGroupActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                                              ObjectStorageGui *storage)
    : ActionGui(editor, storage),
      _groupAction(std::dynamic_pointer_cast<game::stateMachine::actions::ObjectGroupAction<T>>(_baseActionPointer))
{
}

template <typename T>
void ObjectGroupActionGui<T>::onInspect()
{
    ImGui::Text("Operating objects");
    for (const auto &objName : _groupAction->bodyNames())
    {
        if (ImGui::Selectable(objName.c_str()))
        {
            _objectStorageGui->setFocus(objName);
        }
    }
}

template <typename T>
void ObjectGroupActionGui<T>::onEdit()
{
    gui_utils::NamedObjectSelector("Add object to action",
                                   _selectedObjectToAdd,
                                   _groupAction->getNamespacePointer()->getAllNames());
}

template <typename T>
void ObjectGroupActionGui<T>::onSubmitEdit()
{
    _groupAction->addObjectName(_selectedObjectToAdd->name());
}
} // namespace ample::gui
