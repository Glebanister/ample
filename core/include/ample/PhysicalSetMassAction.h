#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalSetMassAction : public PhysicalAction
{
public:
    PhysicalSetMassAction(const std::string &name,
                          const std::vector<std::string> &bodyNames,
                          float mass);
    PhysicalSetMassAction(const filing::JsonIO &input);

    float getMass() const noexcept;

    void setMass(float mass) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _mass;
};
} // namespace ample::game::stateMachine::actions
