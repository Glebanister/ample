#include "PhysicalSetInertiaAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalSetInertiaAction::PhysicalSetInertiaAction(const std::string &name,
                                                   const std::vector<std::string> &bodyNames,
                                                   float inertia)
    : PhysicalAction(name, "PhysicalSetInertiaAction", bodyNames),
      _inertia(inertia) {}

PhysicalSetInertiaAction::PhysicalSetInertiaAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _inertia(input.read<float>("inertia")) {}

float PhysicalSetInertiaAction::getInertia() const noexcept
{
    return _inertia;
}

void PhysicalSetInertiaAction::setInertia(float inertia) noexcept
{
    _inertia = inertia;
}

std::string PhysicalSetInertiaAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("inertia", _inertia);
    return result;
}

void PhysicalSetInertiaAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        auto massData = obj->getMassData();
        massData.I = _inertia;
        obj->setMassData(massData);
    }
}
} // namespace ample::game::stateMachine::actions
