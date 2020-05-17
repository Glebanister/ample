#include "PhysicalApplyTorqueAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalApplyTorqueAction::PhysicalApplyTorqueAction(const std::string &name,
                                                     const std::vector<std::string> &bodyNames,
                                                     float torque,
                                                     bool wake)
    : PhysicalAction(name, "PhysicalApplyTorqueAction", bodyNames),
      _torque(torque),
      _wake(wake) {}

PhysicalApplyTorqueAction::PhysicalApplyTorqueAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _torque(input.read<float>("torque")),
      _wake(input.read<bool>("wake")) {}

float PhysicalApplyTorqueAction::getTorque() const noexcept
{
    return _torque;
}

bool PhysicalApplyTorqueAction::getWake() const noexcept
{
    return _wake;
}

void PhysicalApplyTorqueAction::setTorque(float torque) noexcept
{
    _torque = torque;
}

void PhysicalApplyTorqueAction::setWake(bool wake) noexcept
{
    _wake = wake;
}

std::string PhysicalApplyTorqueAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("torque", _torque);
    result.write<bool>("wake", _wake);
    return result;
}

void PhysicalApplyTorqueAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->applyTorque(_torque, _wake);
    }
}
} // namespace ample::game::stateMachine::actions
