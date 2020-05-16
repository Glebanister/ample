#include <imgui.h>

#include "Utils.h"
#include "objects/PhysicalApplyForceActionGui.h"

namespace ample::gui
{
PhysicalApplyForceActionGui::PhysicalApplyForceActionGui(std::shared_ptr<filing::NamedObject> action,
                                                         std::shared_ptr<game::game2d::Game2dEditor> editor,
                                                         ObjectStorageGui *stor)
    : ObjectGroupActionGui<physics::WorldObject2d>(action, editor, stor)
{
    _action = std::dynamic_pointer_cast<game::stateMachine::actions::PhysicalApplyForceAction>(action);
    _force = _action->getForce();
    _point = _action->getPoint();
}

PhysicalApplyForceActionGui::PhysicalApplyForceActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *stor)
    : ObjectGroupActionGui<physics::WorldObject2d>(editor, stor) {}

void PhysicalApplyForceActionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::InputCoordinates("Force", _force.x, _force.y, 1.0f);
    gui_utils::InputCoordinates("Point", _point.x, _point.y, 1.0f);
}

void PhysicalApplyForceActionGui::onSubmitCreate()
{
    _action = std::make_shared<game::stateMachine::actions::PhysicalApplyForceAction>(nameBuffer,
                                                                                      std::vector<std::string>{},
                                                                                      _force,
                                                                                      _point,
                                                                                      true);
    _baseActionPointer = _action; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void PhysicalApplyForceActionGui::onEdit()
{
    ObjectGroupActionGui<physics::WorldObject2d>::onEdit();
    gui_utils::InputCoordinates("Force", _force.x, _force.y, 1.0f);
    gui_utils::InputCoordinates("Point", _point.x, _point.y, 1.0f);
}

void PhysicalApplyForceActionGui::onSubmitEdit()
{
    ObjectGroupActionGui<physics::WorldObject2d>::onSubmitEdit();
    _action->setForce(_force);
    _action->setPoint(_point);
}

void PhysicalApplyForceActionGui::onView() {}
void PhysicalApplyForceActionGui::onInspect()
{
    ObjectGroupActionGui<physics::WorldObject2d>::onInspect();
}

void PhysicalApplyForceActionGui::onPreview()
{
    ImGui::Text("Force: x %.2f y %.2f", _force.x, _force.y);
    ImGui::Text("Point: x %.2f y %.2f", _point.x, _point.y);
}

std::string PhysicalApplyForceActionGui::name() const
{
    return _action->name();
}

std::string PhysicalApplyForceActionGui::className() const
{
    return "PhysicalApplyForceAction";
}
} // namespace ample::gui
