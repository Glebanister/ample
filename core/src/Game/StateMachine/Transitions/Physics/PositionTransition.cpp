#include "PositionTransition.h"
#include "GameException.h"
#include "ShapesFactory.h"

namespace ample::game::stateMachine::transitions
{
PositionTransition::PositionTransition(const std::string &name,
                                       std::shared_ptr<StateMachine::State> nextState,
                                       const std::vector<std::string> &bodyNames,
                                       const PositionTransition::type &type,
                                       std::unique_ptr<geometry::Shape> shape)
    : PhysicalTransition(name,
                         "PositionTransition",
                         nextState,
                         bodyNames),
      _type(type),
      _shape(std::move(shape))
{
}

PositionTransition::PositionTransition(const filing::JsonIO &input,
                                       std::shared_ptr<StateMachine::State> nextState)
    : PhysicalTransition(input, nextState),
      _type(static_cast<PositionTransition::type>(input.read<int>("type"))),
      _shape(game::factory::ShapesFactory.produce(input, input.read<std::string>("area_type")))
{
    if (_bodyNames.size() < 1)
    {
        throw GameException("can't check position: no objects given");
    }
}

std::string PositionTransition::dump()
{
    filing::JsonIO result = PhysicalTransition::dump();
    result.write<int>("type", static_cast<int>(_type));
    std::string shape = filing::makeField("area", _shape->dump());
    return filing::mergeStrings({result, shape});
}

bool PositionTransition::listen()
{
    ASSERT(_pointersInitialized);
    bool result = true;
    for (const auto &obj : _bodyPointers)
    {
        switch (_type)
        {
        case PositionTransition::type::INSIDE:
            result &= _shape->inside({obj->getX(), obj->getY()});
            break;
        case PositionTransition::type::OUTSIDE:
            result &= !(_shape->inside({obj->getX(), obj->getY()}));
            break;
        }
    }
    return result;
}
} // namespace ample::game::stateMachine::transitions
