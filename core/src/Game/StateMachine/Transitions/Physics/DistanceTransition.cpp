#include "DistanceTransition.h"
#include "GameException.h"

namespace ample::game::stateMachine::transitions
{
DistanceTransition::DistanceTransition(const std::string &name,
                                       std::shared_ptr<StateMachine::State> nextState,
                                       const std::string &firstBodyName,
                                       const std::string &secondBodyName,
                                       const DistanceTransition::type &type,
                                       float distance)
    : PhysicalTransition(name,
                         "DistanceTransition",
                         nextState,
                         firstBodyName,
                         secondBodyName),
      _type(type),
      _distance(distance)
{
}

DistanceTransition::DistanceTransition(const filing::JsonIO &input,
                                       std::shared_ptr<StateMachine::State> nextState)
    : PhysicalTransition(input, nextState),
      _type(static_cast<DistanceTransition::type>(input.read<int>("type"))),
      _distance(input.read<float>("distance"))
{
}

std::string DistanceTransition::dump()
{
    filing::JsonIO result = PhysicalTransition::dump();
    result.write<int>("type", static_cast<int>(_type));
    result.write<int>("distance", _distance);
    return result;
}

void DistanceTransition::onAwake()
{
    PhysicalTransition::onAwake();
    updateObjectPointers();
    _pointersInitialized = true;
}

bool DistanceTransition::listen()
{
    ASSERT(_pointersInitialized);
    float currentDistance = graphics::Vector2d<float>({_firstBodyPointer->getX(), _firstBodyPointer->getY()},
                                                      {_secondBodyPointer->getX(), _secondBodyPointer->getY()})
                                .len();
    switch (_type)
    {
    case type::CLOSER_THAN:
        return currentDistance < _distance;

    case type::FURTHER_THAN:
        return currentDistance > _distance;
    }
    return false;
}
} // namespace ample::game::stateMachine::transitions
