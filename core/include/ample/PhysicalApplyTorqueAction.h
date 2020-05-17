#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalApplyTorqueAction : public PhysicalAction
{
public:
    PhysicalApplyTorqueAction(const std::string &name,
                              const std::vector<std::string> &bodyNames,
                              float torque,
                              bool wake);
    PhysicalApplyTorqueAction(const filing::JsonIO &input);

    float getTorque() const noexcept;

    bool getWake() const noexcept;

    void setTorque(float torque) noexcept;

    void setWake(bool wake) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _torque;
    bool _wake;
};
} // namespace ample::game::stateMachine::actions
