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

void PhysicalTransition::updateObjectPointers()
{
    _firstBodyPointer = getPhysicalObjectPointer(_firstBodyName);
    _secondBodyPointer = getPhysicalObjectPointer(_secondBodyName);
}

std::string PhysicalTransition::dump()
{
    filing::JsonIO result = Transition::dump();
    result.write<std::string>("first_body_name", _firstBodyName);
    result.write<std::string>("second_body_name", _secondBodyName);
    return result;
}

std::shared_ptr<physics::WorldObject2d> PhysicalTransition::getPhysicalObjectPointer(const std::string &name)
{
    std::shared_ptr<physics::WorldObject2d> result;
    try
    {
        result = std::dynamic_pointer_cast<physics::WorldObject2d>(getNamespace().getObject(name));
    }
    catch (const std::bad_cast &e)
    {
        throw GameException("object with name " + name + " is not WorldObject");
    }
    if (!result)
    {
        throw GameException("can not handle physical transition: namespace does not contain object: " + _firstBodyName);
    }
    return result;
}
} // namespace ample::game::stateMachine::transitions
