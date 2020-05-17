#include "PhysicalSetMassAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalSetMassAction::PhysicalSetMassAction(const std::string &name,
                                             const std::vector<std::string> &bodyNames,
                                             float mass)
    : PhysicalAction(name, "PhysicalSetMassAction", bodyNames),
      _mass(mass) {}

PhysicalSetMassAction::PhysicalSetMassAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _mass(input.read<float>("mass")) {}

float PhysicalSetMassAction::getMass() const noexcept
{
    return _mass;
}

void PhysicalSetMassAction::setMass(float mass) noexcept
{
    _mass = mass;
}

std::string PhysicalSetMassAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("mass", _mass);
    return result;
}

void PhysicalSetMassAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        auto massData = obj->getMassData();
        massData.mass = _mass;
        obj->setMassData(massData);
    }
}
} // namespace ample::game::stateMachine::actions
