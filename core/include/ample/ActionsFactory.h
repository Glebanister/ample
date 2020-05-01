#pragma once

#include "Factory.h"
#include "GraphicalRotateAction.h"
#include "GraphicalTranslateAction.h"

namespace ample::game::factory
{
static ample::utils::Factory<Action, const std::string &> ActionsFactory;

namespace registers
{
static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::GraphicalTranslateAction> GraphicalTranslateActionRegister("GraphicalTranslateAction");
static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::GraphicalRotateAction> GraphicalRotateActionRegister("GraphicalRotateAction");
} // namespace registers
} // namespace ample::game::factory
