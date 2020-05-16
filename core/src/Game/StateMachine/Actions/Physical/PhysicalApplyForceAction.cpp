#include "PhysicalApplyForceAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalApplyForceAction::PhysicalApplyForceAction(const std::string &name,
                                                   const std::vector<std::string> &bodyNames,
                                                   const graphics::Vector2d<float> &force,
                                                   const graphics::Vector2d<float> &point,
                                                   bool awake)
    : PhysicalAction(name,
                     "PhysicalApplyForceAction",
                     bodyNames),
      _force(force),
      _point(point),
      _awake(awake) {}

PhysicalApplyForceAction::PhysicalApplyForceAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _force(input.read<graphics::Vector2d<float>>("force")),
      _point(input.read<graphics::Vector2d<float>>("point")),
      _awake(input.read<bool>("awake")) {}

graphics::Vector2d<float> PhysicalApplyForceAction::getForce() const noexcept
{
    return _force;
}

graphics::Vector2d<float> PhysicalApplyForceAction::getPoint() const noexcept
{
    return _point;
}

bool PhysicalApplyForceAction::getAwake() const noexcept
{
    return _awake;
}

void PhysicalApplyForceAction::setForce(const graphics::Vector2d<float> &newForce) noexcept
{
    _force = newForce;
}

void PhysicalApplyForceAction::setPoint(const graphics::Vector2d<float> &newPoint) noexcept
{
    _point = newPoint;
}

void PhysicalApplyForceAction::setAwake(bool awake) noexcept
{
    _awake = awake;
}

std::string PhysicalApplyForceAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<graphics::Vector2d<float>>("force", _force);
    result.write<graphics::Vector2d<float>>("point", _point);
    result.write<bool>("awake", _awake);
    return result;
}

void PhysicalApplyForceAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->applyForceToCenter(_force, _awake); // TODO: stub, should be applyForce
    }
}
} // namespace ample::game::stateMachine::actions
