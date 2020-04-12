#pragma once

#include "Behaviour.h"

namespace ample::game
{
class Action : protected activity::Behavior
{
public:
    void onActive() override;
};
} // namespace ample::game
