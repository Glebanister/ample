#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalAction::PhysicalAction(const std::string &name,
                               const std::string &className,
                               const std::vector<std::string> &bodyNames,
                               const std::function<void(std::shared_ptr<WorldObject2d>)> &function)
    : ObjectGroupAction(name, className, bodyNames),
      _func(function) {}

PhysicalAction::PhysicalAction(const filing::JsonIO &input)
    : ObjectGroupAction(input) {}

void PhysicalAction::onActive()
{
    ObjectGroupAction<WorldObject2d>::onActive();
    std::for_each(_bodyPointers.begin(), _bodyPointers.end(), _func);
}
} // namespace ample::game::stateMachine::actions