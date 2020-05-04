#include "MouseTransition.h"
#include "Debug.h"
#include "Rectangle.h"
#include "ShapesFactory.h"

namespace ample::game
{
MouseTransition::MouseTransition(const std::string &name, std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 relation relativePosition,
                                 control::mouseButton button,
                                 std::unique_ptr<geometry::Shape> area)
    : EnvironmentTransition(name, "MouseTransition", state),
      _eventType(eventType),
      _relation(relativePosition),
      _button(button),
      _area(std::move(area))
{
}

MouseTransition::MouseTransition(const std::string &name,
                                 std::shared_ptr<ample::game::StateMachine::State> state,
                                 type eventType,
                                 relation relativePosition,
                                 control::mouseButton button)
    : MouseTransition(name,
                      state,
                      eventType,
                      relativePosition,
                      button,
                      nullptr)
{
}

MouseTransition::MouseTransition(const filing::JsonIO &input,
                                 std::shared_ptr<ample::game::StateMachine::State> nextState)
    : MouseTransition(input.read<std::string>("name"),
                      nextState,
                      static_cast<type>(input.read<int>("relation")),
                      static_cast<relation>(input.read<int>("button")),
                      static_cast<control::mouseButton>(input.read<int>("event_type")))
{
    if (input.read<int>("has_area"))
    {
        filing::JsonIO shapeString = input.read<std::string>("area");
        _area = factory::ShapesFactory.produce(shapeString.read<std::string>("class_name"),
                                               shapeString);
    }
}

std::string MouseTransition::dump()
{
    filing::JsonIO result = EnvironmentTransition::dump();
    result.write<int>("event_type", static_cast<int>(_eventType));
    result.write<int>("relation", static_cast<int>(_relation));
    result.write<int>("button", static_cast<int>(_button));
    result.write<int>("has_area", static_cast<bool>(_area));
    if (_area)
    {
        result = filing::mergeStrings({result,
                                       filing::makeField("area", _area->dump())});
    }
    return result;
}

bool MouseTransition::listen()
{
    bool result = false;

    graphics::Vector2d<float> mousePosition = {static_cast<float>(control::EventManager::instance().mouse().getMouseX()),
                                               static_cast<float>(control::EventManager::instance().mouse().getMouseY())};

    bool mouseInside = _area ? _area->inside(mousePosition) : true;
    if (_relation == MouseTransition::relation::OUTSIDE)
    {
        mouseInside ^= 1;
    }
    if (mouseInside)
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
