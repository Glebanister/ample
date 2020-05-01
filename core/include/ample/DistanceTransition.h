#pragma once

#include "PhysicalTransition.h"

/*
Class: DistanceTransition

DistanceTransition::type
    - CLOSER_THAN -- all 'bodyNames'
        are closer than 'distance' pairwise
    - FURTHER_THAN -- all 'bodyNames'
        are further than 'distance' pairwise
*/

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
                       const std::vector<std::string> &bodyNames,
                       const DistanceTransition::type &type,
                       float distance);
    DistanceTransition(const filing::JsonIO &input,
                       std::shared_ptr<StateMachine::State> nextState);
    std::string dump() override;

    bool listen() override;

private:
    DistanceTransition::type _type;
    bool _pointersInitialized = false;
    float _distance;
};
} // namespace ample::game::stateMachine::transitions
