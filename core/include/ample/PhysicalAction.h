#pragma once

#include "ObjectGroupAction.h"
#include "WorldObject2d.h"

namespace ample::game::stateMachine::actions
{
template <class Function>
class PhysicalAction : public ObjectGroupAction<graphics::GraphicalObject>
{
public:
    using ObjectGroupAction<graphics::GraphicalObject>::ObjectGroupAction;
    void onActive() override;
};
} // namespace ample::game::stateMachine::actions

#include "templates/PhysicalAction.hpp"
