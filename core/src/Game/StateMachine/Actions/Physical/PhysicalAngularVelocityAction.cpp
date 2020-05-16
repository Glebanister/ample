#include "PhysicalAngularVelocityAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalAngularVelocityAction::PhysicalAngularVelocityAction(const std::string &name,
                                                             const std::vector<std::string> &bodyNames,
                                                             float angularVelocity)
    : PhysicalAction(name,
                     "PhysicalAngularVelocityAction",
                     bodyNames),
      _angularVelocity(angularVelocity) {}

PhysicalAngularVelocityAction::PhysicalAngularVelocityAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _angularVelocity(input.read<float>("angular_valocity")) {}

float PhysicalAngularVelocityAction::getAngularVelocity() const noexcept
{
    return _angularVelocity;
}

void PhysicalAngularVelocityAction::setAngularVelocity(float newAngularVelocity) noexcept
{
    _angularVelocity = newAngularVelocity;
}

std::string PhysicalAngularVelocityAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("angular_valocity", _angularVelocity);
    return result;
}

void PhysicalAngularVelocityAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setAngularVelocity(_angularVelocity);
    }
}
} // namespace ample::game::stateMachine::actions