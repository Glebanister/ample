#pragma once

#include "PhysicalAction.h"

namespace ample::game::stateMachine::actions
{
class PhysicalSetInertiaAction : public PhysicalAction
{
    PhysicalSetInertiaAction(const std::string &name,
                             const std::vector<std::string> &bodyNames,
                             float inertia);
    PhysicalSetInertiaAction(const filing::JsonIO &input);

    float getInertia() const noexcept;

    void setInertia(float inertia) noexcept;

    std::string dump() override;

    void onActive() override;

private:
    float _inertia;
};
} // namespace ample::game::stateMachine::actions
