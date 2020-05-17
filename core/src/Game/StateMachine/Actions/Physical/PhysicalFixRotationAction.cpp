#include "PhysicalFixRotationAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalFixRotationAction::PhysicalFixRotationAction(const std::string &name,
                                                     const std::vector<std::string> &bodyNames,
                                                     bool flag)
    : PhysicalAction(name, "PhysicalFixRotationAction", bodyNames),
      _flag(flag) {}

PhysicalFixRotationAction::PhysicalFixRotationAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _flag(input.read<bool>("flag")) {}

bool PhysicalFixRotationAction::getFlag() const noexcept
{
    return _flag;
}

void PhysicalFixRotationAction::setFlag(bool flag) noexcept
{
    _flag = flag;
}

std::string PhysicalFixRotationAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<bool>("flag", _flag);
    return result;
}

void PhysicalFixRotationAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setFixedRotation(_flag);
    }
}
} // namespace ample::game::stateMachine::actions
