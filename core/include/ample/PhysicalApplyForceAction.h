#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalApplyForceAction : public PhysicalAction
{
    PhysicalApplyForceAction(const std::string &name,
                             const std::vector<std::string> &bodyNames,
                             const graphics::Vector2d<float> &force,
                             const graphics::Vector2d<float> &point,
                             bool awake);
    PhysicalApplyForceAction(const filing::JsonIO &input);

    graphics::Vector2d<float> getForce() const noexcept;
    graphics::Vector2d<float> getPoint() const noexcept;

    bool getAwake() const noexcept;

    void setForce(const graphics::Vector2d<float> &newForce) noexcept;
    void setPoint(const graphics::Vector2d<float> &newPoint) noexcept;

    void setAwake(bool awake) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    graphics::Vector2d<float> _force;
    graphics::Vector2d<float> _point;
    bool _awake;
};
} // namespace ample::game::stateMachine::actions
