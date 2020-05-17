#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalLinearDampingAction : public PhysicalAction
{
    PhysicalLinearDampingAction(const std::string &name,
                                const std::vector<std::string> &bodyNames,
                                float linearDamping);
    PhysicalLinearDampingAction(const filing::JsonIO &input);

    float getLineardamping() const noexcept;

    void setLineardamping(float linearDamping) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _linearDamping;
};
} // namespace ample::game::stateMachine::actions
