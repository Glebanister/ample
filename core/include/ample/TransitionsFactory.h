#pragma once

#include "DistanceTransition.h"
#include "Factory.h"
#include "KeyboardTransition.h"
#include "MouseTransition.h"
#include "PositionTransition.h"
#include "StateMachine.h"
#include "TimerTransition.h"

namespace ample::game::factory
{
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>> TransitionsFactory;

namespace registers
{
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<MouseTransition> MouseTransitionRegister("MouseTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<KeyboardTransition> KeyboardTransitionRegister("KeyboardTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<TimerTransition> TimerTransitionRegister("TimerTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<stateMachine::transitions::DistanceTransition> DistanceTransitionRegister("DistanceTransition");
static ample::utils::Factory<game::StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>>::Register<stateMachine::transitions::PositionTransition> PositionTransitionRegister("PositionTransition");
} // namespace registers
} // namespace ample::game::factory
