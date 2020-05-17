#pragma once

#include "GameException.h"
#include "StateMachine.h"
#include "WorldObject2d.h"

namespace ample::game::stateMachine::transitions
{
class PhysicalTransition : public StateMachine::Transition
{
public:
    PhysicalTransition(const std::string &name,
                       const std::string &className,
                       std::shared_ptr<StateMachine::State> nextState,
                       const std::vector<std::string> &bodyNames);
    PhysicalTransition(const filing::JsonIO &input,
                       std::shared_ptr<StateMachine::State> nextState);
    std::string dump() override;

    void addObjectName(const std::string &);
    std::vector<std::string> &getBodyNames();

    void onStart() override;

protected:
    std::vector<std::string> _bodyNames;
    std::vector<std::shared_ptr<physics::WorldObject2d>> _bodyPointers;
    bool _pointersInitialized;

private:
    void updateObjectPointers();
    std::shared_ptr<physics::WorldObject2d> getPhysicalObjectPointer(const std::string &name);
};
} // namespace ample::game::stateMachine::transitions
