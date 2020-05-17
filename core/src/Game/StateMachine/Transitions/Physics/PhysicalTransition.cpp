#include "PhysicalTransition.h"

namespace ample::game::stateMachine::transitions
{
PhysicalTransition::PhysicalTransition(const std::string &name,
                                       const std::string &className,
                                       std::shared_ptr<StateMachine::State> nextState,
                                       const std::vector<std::string> &bodyNames)
    : Transition(name, className, nextState),
      _bodyNames(std::move(bodyNames))
{
}

PhysicalTransition::PhysicalTransition(const filing::JsonIO &input,
                                       std::shared_ptr<StateMachine::State> nextState)
    : PhysicalTransition(input.read<std::string>("name"),
                         input.read<std::string>("class_name"),
                         nextState,
                         input.read<std::vector<std::string>>("body_names"))
{
}

void PhysicalTransition::updateObjectPointers()
{
    _bodyPointers.resize(_bodyNames.size());
    for (size_t i = 0; i < _bodyNames.size(); ++i)
    {
        _bodyPointers[i] = getPhysicalObjectPointer(_bodyNames[i]);
    }
}

void PhysicalTransition::addObjectName(const std::string &nm)
{
    _bodyNames.push_back(nm);
}
std::vector<std::string> &PhysicalTransition::getBodyNames()
{
    return _bodyNames;
}

void PhysicalTransition::onStart()
{
    updateObjectPointers();
    _pointersInitialized = true;
}

std::string PhysicalTransition::dump()
{
    filing::JsonIO result = Transition::dump();
    result.write<std::vector<std::string>>("body_names", _bodyNames);
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
        throw GameException("can not handle physical transition: namespace does not contain object: " + name);
    }
    return result;
}
} // namespace ample::game::stateMachine::transitions
