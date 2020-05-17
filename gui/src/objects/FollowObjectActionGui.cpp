#include "objects/FollowObjectActionGui.h"
#include "Utils.h"
#include "ObjectStorageGui.h"

namespace ample::gui
{
FollowObjectActionGui::FollowObjectActionGui(std::shared_ptr<filing::NamedObject> obj,
                                             std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(obj, editor, storage),
      _followAction(std::dynamic_pointer_cast<game::stateMachine::actions::FollowObjectAction>(obj))
{
    std::memcpy(cameraName, _followAction->getCameraName().c_str(), sizeof(cameraName));
    std::memcpy(objectName, _followAction->getObjectName().c_str(), sizeof(cameraName));
    slowdown = _followAction->getSlowdown();
}

FollowObjectActionGui::FollowObjectActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(editor, storage)
{
}

void FollowObjectActionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    ImGui::InputText("Camera name", cameraName, 255);
    ImGui::InputText("Object name", objectName, 255);
    gui_utils::InputCoordinates("Slowdown", slowdown.x, slowdown.y, slowdown.z, 0.2f);
}

void FollowObjectActionGui::onSubmitCreate()
{
    _followAction = std::make_shared<game::stateMachine::actions::FollowObjectAction>(nameBuffer, cameraName, objectName);
    _baseActionPointer = _followAction;
}

void FollowObjectActionGui::onEdit()
{
    ImGui::InputText("Camera name", cameraName, 255);
    ImGui::InputText("Object name", objectName, 255);
    gui_utils::InputCoordinates("Slowdown", slowdown.x, slowdown.y, slowdown.z, 0.2f);
}

void FollowObjectActionGui::onSubmitEdit()
{
    if (cameraName)
    {
        _followAction->setCameraName(cameraName);
    }
    if (objectName)
    {
        _followAction->setObjectName(objectName);
    }
    _followAction->setSlowdown(slowdown);
}

void FollowObjectActionGui::onView()
{
    // TODO
}

void FollowObjectActionGui::onInspect()
{
    ImGui::Text("Camera");
    if (ImGui::Selectable(cameraName))
    {
        _objectStorageGui->setFocus(cameraName);
    }
    ImGui::Text("Following object");
    if (ImGui::Selectable(objectName))
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
