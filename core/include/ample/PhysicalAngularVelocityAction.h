#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalAngularVelocityAction : public PhysicalAction
{
public:
    PhysicalAngularVelocityAction(const std::string &name,
                                  const std::vector<std::string> &bodyNames,
                                  float angularVelocity);
    PhysicalAngularVelocityAction(const filing::JsonIO &input);

    float getAngularVelocity() const noexcept;

    void setAngularVelocity(float newAngularVelocity) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _angularVelocity;
};
} // namespace ample::game::stateMachine::actions
