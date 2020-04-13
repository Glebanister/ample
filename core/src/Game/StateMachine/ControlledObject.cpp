#include "ControlledObject.h"
#include "GameException.h"

namespace ample::game
{
ControlledObject::ControlledObject(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className),
      _stateMachine(std::make_shared<StateMachine>())
{
    addBehavior(std::static_pointer_cast<Behavior>(_stateMachine));
}

std::shared_ptr<StateMachine> ControlledObject::stateMachine() noexcept
{
    return _stateMachine;
}
} // namespace ample::game
