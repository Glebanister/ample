#pragma once

#include "StateMachine.h"
#include "WorldObject2d.h"
#include "GameException.h"

namespace ample::game::stateMachine::transitions
{
class PhysicalTransition : public StateMachine::Transition
{
public:
    PhysicalTransition(const std::string &name,
                       const std::string &className,
                       std::shared_ptr<StateMachine::State> nextState,
                       const std::string &firstBodyName,
                       const std::string &secondBodyName);
    PhysicalTransition(const filing::JsonIO &input,
                       std::shared_ptr<StateMachine::State> nextState);
    std::string dump() override;

    void updateObjectPointers();

protected:
    std::string _firstBodyName, _secondBodyName;
    std::shared_ptr<physics::WorldObject2d> _firstBodyPointer;
    std::shared_ptr<physics::WorldObject2d> _secondBodyPointer;

private:
    std::shared_ptr<physics::WorldObject2d> getPhysicalObjectPointer(const std::string &name);
};
} // namespace ample::game::stateMachine::transitions
