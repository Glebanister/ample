#pragma once

#include "ample/PhysicalApplyForceAction.h"

#include "objects/ObjectGroupActionGui.h"

namespace ample::gui
{
class ActionGui;
class PhysicalApplyForceActionGui : public ObjectGroupActionGui<physics::WorldObject2d>
{
public:
    PhysicalApplyForceActionGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);
    PhysicalApplyForceActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *);

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
    std::shared_ptr<game::stateMachine::actions::PhysicalApplyForceAction> _action;

    char nameBuffer[255] = {0};
    graphics::Vector2d<float> _force = {1.0f, 0.0f};
    graphics::Vector2d<float> _point = {0.0f, 0.0f};
};
} // namespace ample::gui
