#include "ControlledObject.h"
#include "GameException.h"

namespace ample::game
{
ControlledObject::ControlledObject(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className),
      _stateMachine(std::make_shared<StateMachine>(name + ".state_machine"))
{
    addBehavior(_stateMachine);
    _idle = std::make_shared<StateMachine::State>(*_stateMachine, "idle");
    _stateMachine->setStartState(_idle);
}

StateMachine &ControlledObject::stateMachine() noexcept
{
    return *_stateMachine;
}

ControlledObject::ControlledObject(const filing::JsonIO &input)
    : NamedStoredObject(input),
      _stateMachine(std::make_shared<StateMachine>(input.updateJsonIO("state_machine")))
{
}

std::shared_ptr<StateMachine::State> ControlledObject::idleState() const noexcept
{
    return _idle;
}

std::string ControlledObject::dump()
{
    return filing::mergeStrings({
        NamedStoredObject::dump(),
        filing::makeField("state_machine", _stateMachine->dump()),
    });
}
} // namespace ample::game
