#pragma once

#include "PhysicalTransition.h"

namespace ample::game::stateMachine::transitions
{
class DistanceTransition : public PhysicalTransition
{
public:
    enum class type
    {
        CLOSER_THAN,
        FURTHER_THAN
    }; // TODO: in interval

public:
    DistanceTransition(const std::string &name,
                       std::shared_ptr<StateMachine::State> nextState,
                       const std::string &firstBodyName,
                       const std::string &secondBodyName,
                       const DistanceTransition::type &type,
                       float distance);
    DistanceTransition(const filing::JsonIO &input,
                       std::shared_ptr<StateMachine::State> nextState);
    std::string dump() override;

    void onAwake() override;

    bool listen() override;

private:
    DistanceTransition::type _type;
    bool _pointersInitialized = false;
    float _distance;
};
} // namespace ample::game::stateMachine::transitions
