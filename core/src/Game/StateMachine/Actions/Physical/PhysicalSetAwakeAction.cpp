#include "PhysicalSetAwakeAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalSetAwakeAction::PhysicalSetAwakeAction(const std::string &name,
                                               const std::vector<std::string> &bodyNames,
                                               bool flag)
    : PhysicalAction(name, "PhysicalSetAwakeAction", bodyNames),
      _flag(flag) {}

PhysicalSetAwakeAction::PhysicalSetAwakeAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _flag(input.read<bool>("flag")) {}

bool PhysicalSetAwakeAction::getFlag() const noexcept
{
    return _flag;
}

void PhysicalSetAwakeAction::setFlag(bool flag) noexcept
{
    _flag = flag;
}

std::string PhysicalSetAwakeAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<bool>("flag", _flag);
    return result;
}

void PhysicalSetAwakeAction::onActive()
{
    PhysicalAction::onActive();
    for (auto &obj : bodyPointers())
    {
        obj->setAwake(_flag);
    }
}
} // namespace ample::game::stateMachine::actions
