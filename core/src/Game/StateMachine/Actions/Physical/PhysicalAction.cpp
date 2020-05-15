#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalAction::PhysicalAction(const std::string &name,
                               const std::string &className,
                               const std::vector<std::string> &bodyNames)
    : ObjectGroupAction(name, className, bodyNames) {}

PhysicalAction::PhysicalAction(const filing::JsonIO &input)
    : ObjectGroupAction(input) {}
} // namespace ample::game::stateMachine::actions