#include "ObjectStorageGui.h"
#include "Utils.h"
#include "objects/CameraTranslateActionGui.h"

namespace ample::gui
{
CameraTranslateActionGui::CameraTranslateActionGui(std::shared_ptr<filing::NamedObject> obj,
                                             std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(obj, editor, storage),
      _translateAction(std::dynamic_pointer_cast<game::stateMachine::actions::CameraTranslateAction>(obj))
{
    std::memcpy(cameraName, _translateAction->getCameraName().c_str(), sizeof(cameraName));
    vector = _translateAction->getVector();
}

CameraTranslateActionGui::CameraTranslateActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                                             ObjectStorageGui *storage)
    : ActionGui(editor, storage)
{
}

void CameraTranslateActionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    ImGui::InputText("Camera name", cameraName, 255);
    gui_utils::InputScalar("Vector x", vector.x, 1.0f);
    gui_utils::InputScalar("Vector y", vector.y, 1.0f);
    gui_utils::InputScalar("Vector z", vector.z, 1.0f);
}

void CameraTranslateActionGui::onSubmitCreate()
{
    _translateAction = std::make_shared<game::stateMachine::actions::CameraTranslateAction>(nameBuffer, cameraName, vector);
    _baseActionPointer = _translateAction;
}

void CameraTranslateActionGui::onEdit()
{
    ImGui::InputText("Camera name", cameraName, 255);
    gui_utils::InputScalar("Vector x", vector.x, 1.0f);
    gui_utils::InputScalar("Vector y", vector.y, 1.0f);
    gui_utils::InputScalar("Vector z", vector.z, 1.0f);
}

void CameraTranslateActionGui::onSubmitEdit()
{
    if (cameraName)
    {
        _translateAction->setCameraName(cameraName);
    }
    _translateAction->setVector(vector);
}

void CameraTranslateActionGui::onView()
{
    // TODO
}

void CameraTranslateActionGui::onInspect()
{
    ImGui::Text("Camera");
    if (ImGui::Selectable(cameraName))
    {
        _objectStorageGui->setFocus(cameraName);
    }
    ImGui::Text("Vector: (%2.f, %2.f, %2.f)", vector.x, vector.y, vector.z);
}

void CameraTranslateActionGui::onPreview()
{
    // TODO
}

std::string CameraTranslateActionGui::name() const
{
    return _translateAction->name();
}
std::string CameraTranslateActionGui::className() const
{
    return "CameraTranslateAction";
}
} // namespace ample::gui
