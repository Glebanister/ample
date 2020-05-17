#include "PhysicalGravityScaleAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalGravityScaleAction::PhysicalGravityScaleAction(const std::string &name,
                                                       const std::vector<std::string> &bodyNames,
                                                       float scale)
    : PhysicalAction(name, "PhysicalGravityScaleAction", bodyNames),
      _scale(scale) {}

PhysicalGravityScaleAction::PhysicalGravityScaleAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _scale(input.read<float>("scale")) {}

float PhysicalGravityScaleAction::getScale() const noexcept
{
    return _scale;
}

void PhysicalGravityScaleAction::setScale(float scale) noexcept
{
    _scale = scale;
}

std::string PhysicalGravityScaleAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("scale", _scale);
    return result;
}

void PhysicalGravityScaleAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setGravityScale(_scale);
    }
}
} // namespace ample::game::stateMachine::actions
