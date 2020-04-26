#include "KeyboardTransition.h"

namespace ample::game
{

KeyboardTransition::KeyboardTransition(const std::string &name,
                                       std::shared_ptr<StateMachine::State> state,
                                       type pressType,
                                       ample::control::keysym key)
    : EnvironmentTransition(name, "KeyboardTransition", state),
      _pressType(pressType),
      _key(key) {}

KeyboardTransition::KeyboardTransition(const filing::JsonIO &input,
                                       std::shared_ptr<ample::game::StateMachine::State> state)
    : KeyboardTransition(input.read<std::string>("name"),
                         state,
                         static_cast<KeyboardTransition::type>(input.read<int>("press_type")),
                         static_cast<control::keysym>(input.read<int>("keysym")))
{
}

std::string KeyboardTransition::dump()
{
    filing::JsonIO result = EnvironmentTransition::dump();
    result.write<int>("press_type", static_cast<int>(_pressType));
    result.write<int>("keysym", static_cast<int>(_key));
    return result;
}

bool KeyboardTransition::listen()
{
    bool result = false;
    switch (_pressType)
    {
    case type::DOWN:
        result = control::EventManager::instance().keyboard().isKeyDown(_key);
        break;

    case type::NOT_DOWN:
        result = !control::EventManager::instance().keyboard().isKeyDown(_key);
        break;

    case type::PRESSED:
        result = control::EventManager::instance().keyboard().isKeyPressed(_key);
        break;

    case type::RELEASED:
        result = control::EventManager::instance().keyboard().isKeyReleased(_key);
        break;
    }
    return result;
}
} // namespace ample::game
