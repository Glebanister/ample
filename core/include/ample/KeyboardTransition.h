#pragma once

#include "EventManager.h"
#include "EnvironmentTransition.h"

namespace ample::game
{
class KeyboardTransition : public EnvironmentTransition
{
public:
    enum class type
    {
        DOWN,
        NOT_DOWN,
        PRESSED,
        RELEASED,
    };

public:
    KeyboardTransition(ample::game::StateMachine::State &state,
                       ample::control::EventManager &manager,
                       type pressType,
                       ample::control::keysym key);

    bool listen() override;

private:
    type _pressType;
    ample::control::keysym _key;
};
} // namespace ample::game
