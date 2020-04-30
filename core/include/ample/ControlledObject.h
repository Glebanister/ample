#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Action.h"
#include "Behaviour.h"
#include "NamedStoredObject.h"
#include "StateMachine.h"

namespace ample::game
{
class ControlledObject : public activity::Behavior, public filing::NamedStoredObject
{
public:
    using NamedStoredObject::NamedStoredObject;
};
} // namespace ample::game

#include "templates/ControlledObject.hpp"
