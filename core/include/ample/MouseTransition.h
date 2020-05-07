#pragma once

#include <functional>
#include <memory>

#include "EventManager.h"
#include "EnvironmentTransition.h"
#include "Vector2d.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Point.h"
#include "Circle.h"

namespace ample::game
{
class MouseTransition : public EnvironmentTransition
{
public:
    enum class type
    {
        PRESSED,
        RELEASED,
        DOWN,
        NOT_DOWN,
        MOVE,
        SCROLL_UP,
        SCROLL_DOWN,
    };

public:
    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> state,
                    type eventType,
                    control::mouseButton button,
                    const geometry::Point &area);

    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> state,
                    type eventType,
                    control::mouseButton button,
                    const geometry::Rectangle &area);

    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> state,
                    type eventType,
                    control::mouseButton button,
                    const geometry::Circle &area);

    bool listen() override;

private:
    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> state,
                    type eventType,
                    control::mouseButton button,
                    std::shared_ptr<geometry::Shape> area);
    type _eventType;
    control::mouseButton _button;
    std::shared_ptr<geometry::Shape> _area;
};
} // namespace ample::game
