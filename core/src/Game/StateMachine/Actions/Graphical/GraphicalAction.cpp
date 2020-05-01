#include <algorithm>

#include "GraphicalAction.h"
#include "Action.h"

namespace ample::game::stateMachine::actions
{
GraphicalAction::GraphicalAction(const std::string &name,
                                 const std::string &className,
                                 const std::vector<std::string> &bodyNames,
                                 const std::function<void(std::shared_ptr<graphics::GraphicalObject>)> &function)
    : ObjectGroupAction(name, className, bodyNames),
      _f(function)
{
}

GraphicalAction::GraphicalAction(const filing::JsonIO &input)
    : ObjectGroupAction(input) {}

void GraphicalAction::onActive()
{
    ObjectGroupAction<graphics::GraphicalObject>::onActive();
    std::for_each(_bodyPointers.begin(), _bodyPointers.end(), _f);
}
} // namespace ample::game::stateMachine::actions
