#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalGravityScaleAction : public PhysicalAction
{
public:
    PhysicalGravityScaleAction(const std::string &name,
                               const std::vector<std::string> &bodyNames,
                               float scale);
    PhysicalGravityScaleAction(const filing::JsonIO &input);

    float getScale() const noexcept;

    void setScale(float scale) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _scale;
};
} // namespace ample::game::stateMachine::actions
