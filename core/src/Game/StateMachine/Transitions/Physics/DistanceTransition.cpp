#include "DistanceTransition.h"
#include "GameException.h"

namespace ample::game::stateMachine::transitions
{
DistanceTransition::DistanceTransition(const std::string &name,
                                       std::shared_ptr<StateMachine::State> nextState,
                                       const std::vector<std::string> &bodyNames,
                                       const DistanceTransition::type &type,
                                       float distance)
    : PhysicalTransition(name,
                         "DistanceTransition",
                         nextState,
                         bodyNames),
      _type(type),
      _distance(distance)
{
    if (_bodyNames.size() < 2)
    {
        throw GameException("can't calculate distance: only one object given");
    }
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

bool DistanceTransition::listen()
{
    ASSERT(_pointersInitialized);
    float minDistance = graphics::Vector2d<float>({_bodyPointers[0]->getX(), _bodyPointers[0]->getY()},
                                                  {_bodyPointers[1]->getX(), _bodyPointers[1]->getY()})
                            .len();
    float maxDistance = minDistance;

    for (size_t i = 0; i < _bodyPointers.size(); ++i)
    {
        for (size_t j = i + 1; j < _bodyPointers.size(); ++j)
        {
            float curDistance = graphics::Vector2d<float>({_bodyPointers[i]->getX(), _bodyPointers[i]->getY()},
                                                          {_bodyPointers[j]->getX(), _bodyPointers[j]->getY()})
                                    .len();
            minDistance = std::min(minDistance, curDistance);
            maxDistance = std::min(maxDistance, curDistance);
        }
    }

    switch (_type)
    {
    case type::CLOSER_THAN:
        return maxDistance < _distance;

    case type::FURTHER_THAN:
        return minDistance > _distance;
    }
    return false;
}
} // namespace ample::game::stateMachine::transitions
