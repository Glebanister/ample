#include "Action.h"

namespace ample::game
{
Action::Action(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className) {}

Action::Action(const filing::JsonIO &input)
    : NamedStoredObject(input) {}
} // namespace ample::game
