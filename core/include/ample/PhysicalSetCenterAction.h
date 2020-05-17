#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalSetCenterAction : public PhysicalAction
{
public:
    PhysicalSetCenterAction(const std::string &name,
                            const std::vector<std::string> &bodyNames,
                            const graphics::Vector2d<float> &center);
    PhysicalSetCenterAction(const filing::JsonIO &input);

    graphics::Vector2d<float> getCenter() const noexcept;

    void setCenter(const graphics::Vector2d<float> &center) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    graphics::Vector2d<float> _center;
};
} // namespace ample::game::stateMachine::actions
