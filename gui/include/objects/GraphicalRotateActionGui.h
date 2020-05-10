#pragma once

#include "ample/GraphicalRotateAction.h"

#include "objects/ActionGui.h"

namespace ample::gui
{
class ActionGui;
class GraphicalRotateActionGui : public ActionGui
{
public:
    GraphicalRotateActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    GraphicalRotateActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

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
    std::shared_ptr<game::stateMachine::actions::GraphicalRotateAction> _rotateAction;

    char nameBuffer[255] = {0};
    graphics::Vector3d<float> axis = {0.0f, 0.0f, 1.0f};
    float angle = 0.0f;
};
} // namespace ample::gui
