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
using utils::Factory;

static Factory<StateMachine::Transition, const std::string &, std::shared_ptr<StateMachine::State>> TransitionsFactory;

namespace registers
{
static decltype(TransitionsFactory)::Register<MouseTransition> MouseTransitionRegister("MouseTransition");
static decltype(TransitionsFactory)::Register<KeyboardTransition> KeyboardTransitionRegister("KeyboardTransition");
static decltype(TransitionsFactory)::Register<TimerTransition> TimerTransitionRegister("TimerTransition");
static decltype(TransitionsFactory)::Register<stateMachine::transitions::DistanceTransition> DistanceTransitionRegister("DistanceTransition");
static decltype(TransitionsFactory)::Register<stateMachine::transitions::PositionTransition> PositionTransitionRegister("PositionTransition");
} // namespace registers
} // namespace ample::factory
