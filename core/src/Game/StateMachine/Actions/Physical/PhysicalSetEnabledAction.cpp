#include "PhysicalSetEnabledAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalSetEnabledAction::PhysicalSetEnabledAction(const std::string &name,
                                                   const std::vector<std::string> &bodyNames,
                                                   bool flag)
    : PhysicalAction(name, "PhysicalSetEnabledAction", bodyNames),
      _flag(flag) {}

PhysicalSetEnabledAction::PhysicalSetEnabledAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _flag(input.read<bool>("flag")) {}

bool PhysicalSetEnabledAction::getFlag() const noexcept
{
    return _flag;
}

void PhysicalSetEnabledAction::setFlag(bool flag) noexcept
{
    _flag = flag;
}

std::string PhysicalSetEnabledAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<bool>("flag", _flag);
    return result;
}

void PhysicalSetEnabledAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setEnabled(_flag);
    }
}
} // namespace ample::game::stateMachine::actions
