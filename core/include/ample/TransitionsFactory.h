#pragma once

#include "Factory.h"
#include "StateMachine.h"
#include "MouseTransition.h"
#include "KeyboardTransition.h"
#include "TimerTransition.h"
#include "DistanceTransition.h"
#include "PositionTransition.h"

namespace ample::game::factory
{
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>> TransitionsFactory;
// static ample::utils::Factory<game::StateMachine::Transition, const std::string &>::Register<game::MouseTransition> MouseTransitionRegister("MouseTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<KeyboardTransition> KeyboardTransitionRegister("KeyboardTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<TimerTransition> TimerTransitionRegister("TimerTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<stateMachine::transitions::DistanceTransition> DistanceTransitionRegister("DistanceTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<stateMachine::transitions::PositionTransition> PositionTransitionRegister("PositionTransition");
} // namespace ample::game::factory
