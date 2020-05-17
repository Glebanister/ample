#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalLinearDampingAction : public PhysicalAction
{
public:
    PhysicalLinearDampingAction(const std::string &name,
                                const std::vector<std::string> &bodyNames,
                                float linearDamping);
    PhysicalLinearDampingAction(const filing::JsonIO &input);

    float getLinearDamping() const noexcept;

    void setLinearDamping(float linearDamping) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _linearDamping;
};
} // namespace ample::game::stateMachine::actions
