#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalLinearVelocityAction : public PhysicalAction
{
    PhysicalLinearVelocityAction(const std::string &name,
                                 const std::vector<std::string> &bodyNames,
                                 const graphics::Vector2d<float> &newLinearVelocity);
    PhysicalLinearVelocityAction(const filing::JsonIO &input);

    std::string dump() override;

private:
    graphics::Vector2d<float> _newLinearVelocity;
};
} // namespace ample::game::stateMachine::actions