#pragma once

#include <functional>

#include "GraphicalObject.h"
#include "ObjectGroupAction.h"

namespace ample::game::stateMachine::actions
{
class GraphicalAction : public ObjectGroupAction<graphics::GraphicalObject>
{
public:
    GraphicalAction(const std::string &name,
                    const std::string &className,
                    const std::vector<std::string> &bodyNames);
    GraphicalAction(const filing::JsonIO &input);
};
} // namespace ample::game::stateMachine::actions
