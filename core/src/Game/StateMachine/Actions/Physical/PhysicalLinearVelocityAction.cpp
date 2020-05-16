#include "PhysicalLinearVelocityAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalLinearVelocityAction::PhysicalLinearVelocityAction(const std::string &name,
                                                           const std::vector<std::string> &bodyNames,
                                                           const graphics::Vector2d<float> &linearVelocity)
    : PhysicalAction(name,
                     "PhysicalLinearVelocityAction",
                     bodyNames),
      _linearVelocity(linearVelocity) {}

PhysicalLinearVelocityAction::PhysicalLinearVelocityAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _linearVelocity(input.read<graphics::Vector2d<float>>("linear_velocity")) {}

graphics::Vector2d<float> PhysicalLinearVelocityAction::getLinearVelocity() const noexcept
{
    return _linearVelocity;
}

void PhysicalLinearVelocityAction::setLinearVelocity(const graphics::Vector2d<float> &newLinearVelocity) noexcept
{
    _linearVelocity = newLinearVelocity;
}

std::string PhysicalLinearVelocityAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<graphics::Vector2d<float>>("linear_velocity", _linearVelocity);
    return result;
}

void PhysicalLinearVelocityAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setLinearVelocity(_linearVelocity);
    }
}
} // namespace ample::game::stateMachine::actions