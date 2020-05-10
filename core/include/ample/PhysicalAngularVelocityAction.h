#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalAngularVelocityAction : public PhysicalAction
{
    PhysicalAngularVelocityAction(const std::string &name,
                                  const std::vector<std::string> &bodyNames,
                                  float angularVelocity);
    PhysicalAngularVelocityAction(const filing::JsonIO &input);

    std::string dump() override;

private:
    float _angularVelocity;
};
} // namespace ample::game::stateMachine::actions
