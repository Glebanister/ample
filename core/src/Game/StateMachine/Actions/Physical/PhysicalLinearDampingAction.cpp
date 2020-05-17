#include "PhysicalLinearDampingAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalLinearDampingAction::PhysicalLinearDampingAction(const std::string &name,
                                                         const std::vector<std::string> &bodyNames,
                                                         float linearDamping)
    : PhysicalAction(name, "PhysicalLinearDampingAction", bodyNames),
      _linearDamping(linearDamping) {}

PhysicalLinearDampingAction::PhysicalLinearDampingAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _linearDamping(input.read<float>("linear_damping")) {}

float PhysicalLinearDampingAction::getLinearDamping() const noexcept
{
    return _linearDamping;
}

void PhysicalLinearDampingAction::setLinearDamping(float linearDamping) noexcept
{
    _linearDamping = linearDamping;
}

std::string PhysicalLinearDampingAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("linear_damping", _linearDamping);
    return result;
}

void PhysicalLinearDampingAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setLinearDamping(_linearDamping);
    }
}
} // namespace ample::game::stateMachine::actions
