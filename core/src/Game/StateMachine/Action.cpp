#include "Action.h"

namespace ample::game
{
Action::Action(const std::string &name, const std::string &className)
    : NamedStoredObject(name, className) {}

void ample::game::Action::onActive()
{
    Behavior::onActive();
}
} // namespace ample::game
