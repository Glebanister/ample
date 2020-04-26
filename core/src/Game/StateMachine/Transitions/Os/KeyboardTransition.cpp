#include "KeyboardTransition.h"

namespace ample::game
{

KeyboardTransition::KeyboardTransition(const std::string &name,
                                       std::shared_ptr<StateMachine::State> state,
                                       control::EventManager &manager,
                                       type pressType,
                                       ample::control::keysym key)
    : EnvironmentTransition(name, "KeyboardTransition", state, manager), _pressType(pressType), _key(key) {}

// KeyboardTransition::KeyboardTransition(const filing::JsonIO &input,
//                    std::shared_ptr<ample::game::StateMachine::State> state) {}

// std::string KeyboardTransition::dump()
// {
//     JsonIO result = EnvironmentTransition::dump();
// }

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
