#include "MouseTransition.h"
#include "Debug.h"

namespace ample::game
{
MouseTransition::MouseTransition(const std::string &name, std::shared_ptr<ample::game::StateMachine::State> state,
                                 control::EventManager &manager,
                                 type eventType,
                                 control::mouseButton button,
                                 std::shared_ptr<geometry::Shape> area)
    : EnvironmentTransition(name, "MouseTransition", state, manager),
      _eventType(eventType),
      _button(button),
      _area(area) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 control::EventManager &manager,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Point &area)
    : MouseTransition(name, state, manager, eventType, button, std::make_shared<geometry::Point>(area)) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 control::EventManager &manager,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Circle &area)
    : MouseTransition(name, state, manager, eventType, button, std::make_shared<geometry::Circle>(area)) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 control::EventManager &manager,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Rectangle &area)
    : MouseTransition(name, state, manager, eventType, button, std::make_shared<geometry::Rectangle>(area)) {}

bool MouseTransition::listen()
{
    bool result = false;

    if (_area->inside({static_cast<float>(_manager.mouse().getMouseX()),
                       static_cast<float>(_manager.mouse().getMouseY())}))
    {
        switch (_eventType)
        {
        case type::PRESSED:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = _manager.mouse().isLeftPressed();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = _manager.mouse().isMiddlePressed();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = _manager.mouse().isRightPressed();
                break;
            }
            break;

        case type::RELEASED:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = _manager.mouse().isLeftReleased();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = _manager.mouse().isMiddleReleased();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = _manager.mouse().isRightReleased();
                break;
            }
            break;

        case type::DOWN:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = _manager.mouse().isLeftDown();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = _manager.mouse().isMiddleDown();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = _manager.mouse().isRightDown();
                break;
            }
            break;

        case type::NOT_DOWN:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = !_manager.mouse().isLeftDown();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = !_manager.mouse().isMiddleDown();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = !_manager.mouse().isRightDown();
                break;
            }
            break;

        case type::MOVE:
            result = _manager.mouse().getMouseXRel() || _manager.mouse().getMouseYRel();
            break;

        case type::SCROLL_UP:
            result = _manager.mouse().getWheelY() > 0; // TODO: is it true?
            break;

        case type::SCROLL_DOWN:
            result = _manager.mouse().getWheelY() < 0; // TODO: is it true?
            break;
        }
    }
    return result;
}
} // namespace ample::game
