#include "ControlledObject.h"
#include "GameException.h"

namespace ample::game
{
ControlledObject::ControlledObject(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className),
      _stateMachine(std::make_shared<StateMachine>(name + ".state_machine"))
{
    addBehavior(std::static_pointer_cast<Behavior>(_stateMachine));
    _stateMachine->setStartState(std::make_shared<StateMachine::State>(_stateMachine->shared_from_this(), "idle"));
}

std::shared_ptr<StateMachine> ControlledObject::stateMachine() noexcept
{
    return _stateMachine;
}

ControlledObject::ControlledObject(const filing::JsonIO &input)
    : NamedStoredObject(input),
      _stateMachine(std::make_shared<StateMachine>(input.read<std::string>("state_machine")))
{
}

std::string ControlledObject::dump()
{
    return filing::mergeStrings(
        {
            NamedStoredObject::dump(),
            filing::makeField("state_machine", _stateMachine->dump()),
        });
}
} // namespace ample::game
