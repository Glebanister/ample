#include "objects/FollowObjectActionGui.h"
#include "ObjectStorageGui.h"
#include "Utils.h"

namespace ample::gui
{
FollowObjectActionGui::FollowObjectActionGui(std::shared_ptr<filing::NamedObject> obj,
                                             std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(obj, editor, storage),
      _followAction(std::dynamic_pointer_cast<game::stateMachine::actions::FollowObjectAction>(obj))
{
    cameraName = _followAction->getCameraName();
    objectName = _followAction->getObjectName();
    slowdown = _followAction->getSlowdown();
    std::memcpy(objectNameBuffer, objectName.c_str(), sizeof(objectNameBuffer));
    std::memcpy(cameraNameBuffer, cameraName.c_str(), sizeof(cameraNameBuffer));
}

FollowObjectActionGui::FollowObjectActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(editor, storage)
{
}

void FollowObjectActionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    // ASSERT(_state);
    ImGui::InputText("Camera name", cameraNameBuffer, 255);
    ImGui::InputText("Object name", objectNameBuffer, 255);
    // gui_utils::NamedObjectSelector("Camera",
    //                                cameraName,
    //                                _action->getNamespacePointer()->getAllNames());
    // gui_utils::NamedObjectSelector("Object",
    //                                objectName,
    //                                _state->getNamespacePointer()->getAllNames());
    gui_utils::InputCoordinates("Slowdown", slowdown.x, slowdown.y, slowdown.z, 0.2f);
}

void FollowObjectActionGui::onSubmitCreate()
{
    _followAction = std::make_shared<game::stateMachine::actions::FollowObjectAction>(nameBuffer, cameraName, objectName);
    _baseActionPointer = _followAction;
}

void FollowObjectActionGui::onEdit()
{
    // gui_utils::NamedObjectSelector("Camera",
    //                                cameraName,
    //                                _state->getNamespacePointer()->getAllNames());
    // gui_utils::NamedObjectSelector("Object",
    //                                objectName,
    //                                _state->getNamespacePointer()->getAllNames());
    ImGui::InputText("Camera name", cameraNameBuffer, 255);
    ImGui::InputText("Object name", objectNameBuffer, 255);
    gui_utils::InputCoordinates("Slowdown", slowdown.x, slowdown.y, slowdown.z, 0.1f);
}

void FollowObjectActionGui::onSubmitEdit()
{
    _followAction->setCameraName(cameraNameBuffer);
    _followAction->setObjectName(objectNameBuffer);
    _followAction->setSlowdown(slowdown);
}

void FollowObjectActionGui::onView()
{
    // TODO
}

void FollowObjectActionGui::onInspect()
{
    ImGui::Text("Camera");
    if (ImGui::Selectable(cameraName.c_str()))
    {
        _objectStorageGui->setFocus(cameraName);
    }
    ImGui::Text("Following object");
    if (ImGui::Selectable(objectName.c_str()))
    {
        _objectStorageGui->setFocus(objectName);
    }
}

void FollowObjectActionGui::onPreview()
{
    // TODO
}

std::string FollowObjectActionGui::name() const
{
    return _followAction->name();
}
std::string FollowObjectActionGui::className() const
{
    return "FollowObjectAction";
}
} // namespace ample::gui
