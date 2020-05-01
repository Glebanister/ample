#pragma once

#include "Factory.h"
#include "GraphicalAction.h"
#include "PhysicalAction.h"

namespace ample::game::factory
{
static ample::utils::Factory<Action, const std::string &> ActionsFactory;

namespace registers
{
// static ample::utils::Factory<graphics::GraphicalObject, const std::string &>::Register<graphics::GraphicalObject> GraphicalObjectRegister("GraphicalObject");
} // namespace registers
} // namespace ample::game::factory
