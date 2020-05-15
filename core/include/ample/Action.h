#pragma once

#include "Behaviour.h"
#include "NamedStoredObject.h"

namespace ample::game
{
class Action : protected activity::Behavior, public filing::NamedStoredObject
{
public:
    Action(const std::string &name, const std::string &className);
    Action(const filing::JsonIO &input);
    virtual void addObjectName(const std::string &name) = 0;
    using Behavior::onActive;
};
} // namespace ample::game
