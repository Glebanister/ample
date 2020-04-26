#pragma once

#include "Factory.h"
#include "StateMachine.h"
#include "MouseTransition.h"
#include "KeyboardTransition.h"
#include "TimerTransition.h"

namespace ample::game::factory
{
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<game::StateMachine::State>> TransitionsFactory;
// static ample::utils::Factory<game::StateMachine::Transition, const std::string &>::Register<game::MouseTransition> MouseTransitionRegister("MouseTransition");
// static ample::utils::Factory<game::StateMachine::Transition, const std::string &>::Register<game::KeyboardTransition> KeyboardTransitionRegister("KeyboardTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<game::StateMachine::State>>::Register<game::TimerTransition> TimerTransitionRegister("TimerTransition");
} // namespace ample::game::factory
