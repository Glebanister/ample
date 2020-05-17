#include "PhysicalAngularDampingAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalAngularDampingAction::PhysicalAngularDampingAction(const std::string &name,
                                                           const std::vector<std::string> &bodyNames,
                                                           float angularDamping)
    : PhysicalAction(name, "PhysicalAngularDampingAction", bodyNames),
      _angularDamping(angularDamping) {}

PhysicalAngularDampingAction::PhysicalAngularDampingAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _angularDamping(input.read<float>("angular_damping")) {}

float PhysicalAngularDampingAction::getAngulardamping() const noexcept
{
    return _angularDamping;
}

void PhysicalAngularDampingAction::setAngulardamping(float angularDamping) noexcept
{
    _angularDamping = angularDamping;
}

std::string PhysicalAngularDampingAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("angular_damping", _angularDamping);
    return result;
}

void PhysicalAngularDampingAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setAngularDamping(_angularDamping);
    }
}
} // namespace ample::game::stateMachine::actions
