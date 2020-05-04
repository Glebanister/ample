#pragma once

#include "Factory.h"
#include "StateMachine.h"
#include "Level.h"
#include "Namespace.h"

namespace ample::game::factory
{
using utils::Factory;

static Factory<StateMachine::State, const std::string &, StateMachine &, const Namespace &> StateFactory;

namespace registers
{
static decltype(StateFactory)::Register<StateMachine::State> StateRegister("State");
} // namespace registers
} // namespace ample::factory
