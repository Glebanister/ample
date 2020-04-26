#include "MouseTransition.h"
#include "Debug.h"

namespace ample::game
{
MouseTransition::MouseTransition(const std::string &name, std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 control::mouseButton button,
                                 std::shared_ptr<geometry::Shape> area)
    : EnvironmentTransition(name, "MouseTransition", state),
      _eventType(eventType),
      _button(button),
      _area(area) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Point &area)
    : MouseTransition(name, state, eventType, button, std::make_shared<geometry::Point>(area)) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Circle &area)
    : MouseTransition(name, state, eventType, button, std::make_shared<geometry::Circle>(area)) {}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 control::mouseButton button,
                                 const geometry::Rectangle &area)
    : MouseTransition(name, state, eventType, button, std::make_shared<geometry::Rectangle>(area)) {}

bool MouseTransition::listen()
{
    bool result = false;

    if (_area->inside({static_cast<float>(control::EventManager::instance().mouse().getMouseX()),
                       static_cast<float>(control::EventManager::instance().mouse().getMouseY())}))
    {
        switch (_eventType)
        {
        case type::PRESSED:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = control::EventManager::instance().mouse().isLeftPressed();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = control::EventManager::instance().mouse().isMiddlePressed();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = control::EventManager::instance().mouse().isRightPressed();
                break;
            }
            break;

        case type::RELEASED:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = control::EventManager::instance().mouse().isLeftReleased();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = control::EventManager::instance().mouse().isMiddleReleased();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = control::EventManager::instance().mouse().isRightReleased();
                break;
            }
            break;

        case type::DOWN:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = control::EventManager::instance().mouse().isLeftDown();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = control::EventManager::instance().mouse().isMiddleDown();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = control::EventManager::instance().mouse().isRightDown();
                break;
            }
            break;

        case type::NOT_DOWN:
            switch (_button)
            {
            case control::mouseButton::BUTTON_LEFT:
                result = !control::EventManager::instance().mouse().isLeftDown();
                break;

            case control::mouseButton::BUTTON_MIDDLE:
                result = !control::EventManager::instance().mouse().isMiddleDown();
                break;

            case control::mouseButton::BUTTON_RIGHT:
                result = !control::EventManager::instance().mouse().isRightDown();
                break;
            }
            break;

        case type::MOVE:
            result = control::EventManager::instance().mouse().getMouseXRel() || control::EventManager::instance().mouse().getMouseYRel();
            break;

        case type::SCROLL_UP:
            result = control::EventManager::instance().mouse().getWheelY() > 0; // TODO: is it true?
            break;

        case type::SCROLL_DOWN:
            result = control::EventManager::instance().mouse().getWheelY() < 0; // TODO: is it true?
            break;
        }
    }
    return result;
}
} // namespace ample::game
