#include "EnvironmentTransition.h"

namespace ample::game
{
EnvironmentTransition::EnvironmentTransition(const std::string &name,
                                             const std::string &className,
                                             std::shared_ptr<StateMachine::State> state,
                                             control::EventManager &manager)
    : Transition(name, className, state), _manager(manager) {}
} // namespace ample::game
