#pragma once

#include "Behaviour.h"
#include "NamedStoredObject.h"

namespace ample::game
{
class Action : protected activity::Behavior, public filing::NamedStoredObject
{
public:
    Action(const std::string &name, const std::string &className);
    using Behavior::onActive;
};
} // namespace ample::game
