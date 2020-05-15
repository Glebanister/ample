#pragma once

#include "PhysicalTransition.h"
#include <string_view>
#include <unordered_set>

namespace ample::game::stateMachine::transitions
{
class CollisionTransition : public PhysicalTransition
{
public:
    CollisionTransition(const std::string &name,
                        std::shared_ptr<StateMachine::State> nextState,
                        const std::vector<std::string> &bodyNames,
                        size_t startTriggers);
    CollisionTransition(const filing::JsonIO &input,
                        std::shared_ptr<StateMachine::State> nextState);

    std::string dump() override;

    bool listen() override;

private:
    size_t _triggerStartIdx;
    std::unordered_set<std::string_view> _triggers;
};
} // namespace ample::game::stateMachine::transitions
