#pragma once

#include "StateMachine.h"
#include "EventManager.h"

namespace ample::game
{
class EnvironmentTransition : public StateMachine::Transition
{
public:
    EnvironmentTransition(StateMachine::State &state, control::EventManager &manager);

protected:
    ample::control::EventManager &_manager;
};

} // namespace ample::game
