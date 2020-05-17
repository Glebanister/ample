#include "PhysicalApplyLinearImpAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalApplyLinearImpAction::PhysicalApplyLinearImpAction(const std::string &name,
                                                           const std::vector<std::string> &bodyNames,
                                                           const graphics::Vector2d<float> &impulse,
                                                           const graphics::Vector2d<float> &point,
                                                           bool wake)
    : PhysicalAction(name, "PhysicalApplyLinearImpAction", bodyNames),
      _impulse(impulse),
      _point(point),
      _wake(wake) {}

PhysicalApplyLinearImpAction::PhysicalApplyLinearImpAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _impulse(input.read<graphics::Vector2d<float>>("impulse")),
      _point(input.read<graphics::Vector2d<float>>("point")),
      _wake(input.read<bool>("wake")) {}

graphics::Vector2d<float> PhysicalApplyLinearImpAction::getImpulse() const noexcept
{
    return _impulse;
}

graphics::Vector2d<float> PhysicalApplyLinearImpAction::getPoint() const noexcept
{
    return _point;
}

bool PhysicalApplyLinearImpAction::getWake() const noexcept
{
    return _wake;
}

void PhysicalApplyLinearImpAction::setImpulse(const graphics::Vector2d<float> &impulse) noexcept
{
    _impulse = impulse;
}

void PhysicalApplyLinearImpAction::setPoint(const graphics::Vector2d<float> &point) noexcept
{
    _point = point;
}

void PhysicalApplyLinearImpAction::setWake(bool wake) noexcept
{
    _wake = wake;
}

std::string PhysicalApplyLinearImpAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<graphics::Vector2d<float>>("impulse", _impulse);
    result.write<graphics::Vector2d<float>>("point", _point);
    result.write<bool>("wake", _wake);
    return result;
}

void PhysicalApplyLinearImpAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->applyLinearImpulse(_impulse, _point, _wake);
    }
}
} // namespace ample::game::stateMachine::actions
