#pragma once

#include "Factory.h"
#include "GraphicalRotateAction.h"
#include "GraphicalTranslateAction.h"
#include "FollowObjectAction.h"
#include "CameraTranslateAction.h"
#include "PhysicalApplyForceAction.h"

namespace ample::game::factory
{
static ample::utils::Factory<Action, const std::string &> ActionsFactory;

namespace registers
{
static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::GraphicalTranslateAction> GraphicalTranslateActionRegister("GraphicalTranslateAction");
static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::GraphicalRotateAction> GraphicalRotateActionRegister("GraphicalRotateAction");
static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::PhysicalApplyForceAction> PhysicalApplyForceActionRegister("PhysicalApplyForceAction");
// static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::FollowObjectAction> FollowObjectActionActionRegister("FollowObjectAction");
// static ample::utils::Factory<Action, const std::string &>::Register<ample::game::stateMachine::actions::CameraTranslateAction> CameraTranslateActionActionRegister("CameraTranslateAction");
} // namespace registers
} // namespace ample::game::factory
