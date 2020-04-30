#pragma once

#include "PhysicalTransition.h"
#include "Rectangle.h"
#include "Point.h"
#include "Circle.h"

namespace ample::game::stateMachine::transitions
{
class PositionTransition : public PhysicalTransition
{
public:
    enum class type
    {
        INSIDE,
        OUTSIDE,
    }; // TODO: on edge ?

public:
    PositionTransition(const std::string &name,
                       std::shared_ptr<StateMachine::State> nextState,
                       const std::string &firstBodyName,
                       const std::string &secondBodyName,
                       const PositionTransition::type &type,
                       std::unique_ptr<geometry::Shape> shape);
    PositionTransition(const filing::JsonIO &input,
                       std::shared_ptr<StateMachine::State> nextState);
    std::string dump() override;

    void onAwake() override;

    bool listen() override;

private:
    PositionTransition::type _type;
    bool _pointersInitialized = false;
    std::unique_ptr<geometry::Shape> _shape;
};
} // namespace ample::game::stateMachine::transitions
