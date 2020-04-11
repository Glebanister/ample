#pragma once

#include "Behaviour.h"
#include "StoredObject.h"

namespace ample::game
{
class Action : protected activity::Behavior, public filing::StoredObject
{
public:
    void onActive() override;
};
} // namespace ample::game
