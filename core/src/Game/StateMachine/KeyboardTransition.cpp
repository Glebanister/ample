#include "KeyboardTransition.h"

namespace ample::game
{

KeyboardTransition::KeyboardTransition(ample::game::StateMachine::State &state,
                                       ample::control::EventManager &manager,
                                       type pressType,
                                       ample::control::keysym key)
    : EnvironmentTransition(state, manager), _pressType(pressType), _key(key) {}

bool KeyboardTransition::listen()
{
    bool result = false;
    switch (_pressType)
    {
    case type::DOWN:
        result = _manager.keyboard().isKeyDown(_key);
        break;

    case type::NOT_DOWN:
        result = !_manager.keyboard().isKeyDown(_key);
        break;

    case type::PRESSED:
        result = _manager.keyboard().isKeyPressed(_key);
        break;

    case type::RELEASED:
        result = _manager.keyboard().isKeyReleased(_key);
        break;
    }
    return result;
}
} // namespace ample::game
