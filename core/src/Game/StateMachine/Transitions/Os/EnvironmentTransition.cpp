#include "EnvironmentTransition.h"

namespace ample::game
{
EnvironmentTransition::EnvironmentTransition(std::shared_ptr<StateMachine::State> state,
                                             control::EventManager &manager)
    : Transition(state), _manager(manager) {}
} // namespace ample::game
