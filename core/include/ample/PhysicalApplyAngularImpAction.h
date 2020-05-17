#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalApplyAngularImpAction : public PhysicalAction
{
    PhysicalApplyAngularImpAction(const std::string &name,
                                  const std::vector<std::string> &bodyNames,
                                  float impulse,
                                  bool wake);
    PhysicalApplyAngularImpAction(const filing::JsonIO &input);

    float getImpulse() const noexcept;

    bool getWake() const noexcept;

    void setImpulse(float impulse) noexcept;

    void setWake(bool wake) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _impulse;
    bool _wake;
};
} // namespace ample::game::stateMachine::actions
