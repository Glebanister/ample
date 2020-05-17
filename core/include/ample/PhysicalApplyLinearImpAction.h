#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalApplyLinearImpAction : public PhysicalAction
{
    PhysicalApplyLinearImpAction(const std::string &name,
                                 const std::vector<std::string> &bodyNames,
                                 const graphics::Vector2d<float> &impulse,
                                 const graphics::Vector2d<float> &point,
                                 bool wake);
    PhysicalApplyLinearImpAction(const filing::JsonIO &input);

    graphics::Vector2d<float> getImpulse() const noexcept;

    graphics::Vector2d<float> getPoint() const noexcept;

    bool getWake() const noexcept;

    void setImpulse(const graphics::Vector2d<float> &impulse) noexcept;

    void setPoint(const graphics::Vector2d<float> &point) noexcept;

    void setWake(bool wake) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    graphics::Vector2d<float> _impulse;
    graphics::Vector2d<float> _point;
    bool _wake;
};
} // namespace ample::game::stateMachine::actions
