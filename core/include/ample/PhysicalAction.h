#pragma once

#include "ObjectGroupAction.h"
#include "WorldObject2d.h"
#include <functional>
#include <memory>

namespace ample::game::stateMachine::actions
{
class PhysicalAction : public ObjectGroupAction<physics::WorldObject2d>
{
public:
    PhysicalAction(const std::string &name,
                   const std::string &className,
                   const std::vector<std::string> &bodyNames);
    PhysicalAction(const filing::JsonIO &input);
};
} // namespace ample::game::stateMachine::actions
