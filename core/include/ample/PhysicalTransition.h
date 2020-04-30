#pragma once

#include "StateMachine.h"

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

private:
    std::string _firstBodyName, _secondBodyName;
};
} // namespace ample::game::stateMachine::transitions
