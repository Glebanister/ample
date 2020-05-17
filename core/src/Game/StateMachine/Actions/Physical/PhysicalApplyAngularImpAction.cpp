#include "PhysicalApplyAngularImpAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalApplyAngularImpAction::PhysicalApplyAngularImpAction(const std::string &name,
                                                             const std::vector<std::string> &bodyNames,
                                                             float impulse,
                                                             bool wake)
    : PhysicalAction(name, "PhysicalApplyAngularImpAction", bodyNames),
      _impulse(impulse),
      _wake(wake) {}

PhysicalApplyAngularImpAction::PhysicalApplyAngularImpAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _impulse(input.read<float>("impulse")),
      _wake(input.read<bool>("wake")) {}

float PhysicalApplyAngularImpAction::getImpulse() const noexcept
{
    return _impulse;
}

bool PhysicalApplyAngularImpAction::getWake() const noexcept
{
    return _wake;
}

void PhysicalApplyAngularImpAction::setImpulse(float impulse) noexcept
{
    _impulse = impulse;
}

void PhysicalApplyAngularImpAction::setWake(bool wake) noexcept
{
    _wake = wake;
}

std::string PhysicalApplyAngularImpAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("impulse", _impulse);
    result.write<bool>("wake", _wake);
    return result;
}

void PhysicalApplyAngularImpAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->applyAngularImpulse(_impulse, _wake);
    }
}
} // namespace ample::game::stateMachine::actions
