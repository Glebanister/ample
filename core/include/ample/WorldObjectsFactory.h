#pragma once

#include "Factory.h"
#include "WorldObject2d.h"

namespace ample::game::factory
{
static ample::utils::Factory<physics::WorldObject2d, const std::string &, std::shared_ptr<physics::WorldLayer2d>> WorldObjecsFactory;
static ample::utils::Factory<physics::WorldObject2d, const std::string &, std::shared_ptr<physics::WorldLayer2d>>::Register<physics::WorldObject2d> WorldObject2dRegister("WorldObject2d");
} // namespace ample::game::factory
