#pragma once

#include <memory>

#include "StateMachine.h"
#include "EventManager.h"

namespace ample::game
{
class EnvironmentTransition : public StateMachine::Transition
{
public:
    EnvironmentTransition(const std::string &name,
                          const std::string &className,
                          std::shared_ptr<StateMachine::State> nextState,
                          control::EventManager &manager);

protected:
    ample::control::EventManager &_manager;
};

} // namespace ample::game
