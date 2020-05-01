#pragma once

#include "GraphicalAction.h"

namespace ample::game::stateMachine::actions
{
template <class Function>
void GraphicalAction<Function>::onActive()
{
    Action::onActive();
    ASSERT(_pointersInitialized);
    Function f;
    Action::onActive();
    for (const auto &obj : _bodyPointers)
    {
        f(obj);
    }
}
} // namespace ample::game::stateMachine::actions
