#include "PhysicalSetCenterAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalSetCenterAction::PhysicalSetCenterAction(const std::string &name,
                                                 const std::vector<std::string> &bodyNames,
                                                 const graphics::Vector2d<float> &center)
    : PhysicalAction(name, "PhysicalSetCenterAction", bodyNames),
      _center(center) {}

PhysicalSetCenterAction::PhysicalSetCenterAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _center(input.read<graphics::Vector2d<float>>("center")) {}

graphics::Vector2d<float> PhysicalSetCenterAction::getCenter() const noexcept
{
    return _center;
}

void PhysicalSetCenterAction::setCenter(const graphics::Vector2d<float> &center) noexcept
{
    _center = center;
}

std::string PhysicalSetCenterAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<graphics::Vector2d<float>>("center", _center);
    return result;
}

void PhysicalSetCenterAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        auto massData = obj->getMassData();
        massData.center = _center;
        obj->setMassData(massData);
    }
}
} // namespace ample::game::stateMachine::actions
