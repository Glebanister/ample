#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalLinearVelocityAction : public PhysicalAction
{
public:
    PhysicalLinearVelocityAction(const std::string &name,
                                 const std::vector<std::string> &bodyNames,
                                 const graphics::Vector2d<float> &linearVelocity);
    PhysicalLinearVelocityAction(const filing::JsonIO &input);

    graphics::Vector2d<float> getLinearVelocity() const noexcept;

    void setLinearVelocity(const graphics::Vector2d<float> &newLinearVelocity) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    graphics::Vector2d<float> _linearVelocity;
};
} // namespace ample::game::stateMachine::actions