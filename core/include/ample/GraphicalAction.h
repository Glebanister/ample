#pragma once

#include "ObjectGroupAction.h"
#include "GraphicalObject.h"

namespace ample::game::stateMachine::actions
{
template <class Function>
class GraphicalAction : public ObjectGroupAction<graphics::GraphicalObject>
{
public:
    using ObjectGroupAction<graphics::GraphicalObject>::ObjectGroupAction;
    void onActive() override;
};
} // namespace ample::game::stateMachine::actions

#include "templates/GraphicalAction.hpp"
