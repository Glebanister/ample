#include "EnvironmentTransition.h"

namespace ample::game
{
EnvironmentTransition::EnvironmentTransition(const std::string &name,
                                             const std::string &className,
                                             std::shared_ptr<StateMachine::State> state)
    : Transition(name, className, state) {}
} // namespace ample::game
