#pragma once

#include <functional>
#include <memory>

#include "Circle.h"
#include "EnvironmentTransition.h"
#include "EventManager.h"
#include "Point.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Vector2d.h"

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

    enum class relation
    {
        INSIDE,
        OUTSIDE
    };

public:
    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> nextState,
                    type eventType,
                    relation relativePosition,
                    control::mouseButton button,
                    std::unique_ptr<geometry::Shape> area);

    MouseTransition(const std::string &name,
                    std::shared_ptr<ample::game::StateMachine::State> nextState,
                    type eventType,
                    relation relativePosition,
                    control::mouseButton button);

    MouseTransition(const filing::JsonIO &input,
                    std::shared_ptr<ample::game::StateMachine::State> nextState);

    std::string dump() override;

    bool listen() override;

private:
    type _eventType;
    relation _relation;
    control::mouseButton _button;
    std::unique_ptr<geometry::Shape> _area;
};
} // namespace ample::game
