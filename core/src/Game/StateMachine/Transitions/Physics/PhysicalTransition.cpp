#include "PhysicalTransition.h"

namespace ample::game::stateMachine::transitions
{
PhysicalTransition::PhysicalTransition(const std::string &name,
                                       const std::string &className,
                                       std::shared_ptr<StateMachine::State> nextState,
                                       const std::string &firstBodyName,
                                       const std::string &secondBodyName)
    : Transition(name, className, nextState),
      _firstBodyName(std::move(firstBodyName)),
      _secondBodyName(std::move(secondBodyName))
{
}
PhysicalTransition::PhysicalTransition(const filing::JsonIO &input,
                                       std::shared_ptr<StateMachine::State> nextState)
    : PhysicalTransition(input.read<std::string>("name"),
                         input.read<std::string>("class_name"),
                         nextState,
                         input.read<std::string>("first_body_name"),
                         input.read<std::string>("second_body_name")) {}

std::string PhysicalTransition::dump()
{
    filing::JsonIO result = Transition::dump();
    result.write<std::string>("first_body_name", _firstBodyName);
    result.write<std::string>("second_body_name", _secondBodyName);
    return result;
}
} // namespace ample::game::stateMachine::transitions
