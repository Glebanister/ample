#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalAngularDampingAction : public PhysicalAction
{
public:
    PhysicalAngularDampingAction(const std::string &name,
                                 const std::vector<std::string> &bodyNames,
                                 float angularDamping);
    PhysicalAngularDampingAction(const filing::JsonIO &input);

    float getAngulardamping() const noexcept;

    void setAngulardamping(float angularDamping) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _angularDamping;
};
} // namespace ample::game::stateMachine::actions
