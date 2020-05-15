#include <algorithm>

#include "Action.h"
#include "GraphicalAction.h"

namespace ample::game::stateMachine::actions
{
GraphicalAction::GraphicalAction(const std::string &name,
                                 const std::string &className,
                                 const std::vector<std::string> &bodyNames)
    : ObjectGroupAction(name, className, bodyNames)
{
}

GraphicalAction::GraphicalAction(const filing::JsonIO &input)
    : ObjectGroupAction(input) {}
} // namespace ample::game::stateMachine::actions
