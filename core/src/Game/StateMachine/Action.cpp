#include "Action.h"

namespace ample::game
{
Action::Action(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className) {}
} // namespace ample::game
