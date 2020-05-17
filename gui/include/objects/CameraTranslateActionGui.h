#pragma once

#include "ample/CameraTranslateAction.h"
#include "ample/Vector3d.h"

#include "objects/ActionGui.h"

namespace ample::gui
{
class CameraTranslateActionGui : public ActionGui
{
public:
    CameraTranslateActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    CameraTranslateActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

private:
    std::shared_ptr<game::stateMachine::actions::CameraTranslateAction> _translateAction;
    char nameBuffer[255] = {0};
    char cameraName[255] = {0};
    graphics::Vector3d<float> vector;
};
} // namespace ample::gui
