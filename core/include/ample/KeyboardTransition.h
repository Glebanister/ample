#pragma once

#include "EventManager.h"
#include "EnvironmentTransition.h"
#include "JsonIO.h"

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
    KeyboardTransition(const std::string &name,
                       std::shared_ptr<ample::game::StateMachine::State> state,
                       control::EventManager &manager,
                       type pressType,
                       control::keysym key);

    // KeyboardTransition(const filing::JsonIO &input,
    //                    std::shared_ptr<ample::game::StateMachine::State> state,
    //                    control::EventManager &manager);

    // std::string dump() override;

    bool listen() override;

private:
    type _pressType;
    control::keysym _key;
};
} // namespace ample::game
