#pragma once

#include "ObjectGroupAction.h"
#include "WorldObject2d.h"
#include <functional>
#include <memory>

namespace ample::game::stateMachine::actions
{
class PhysicalAction : public ObjectGroupAction<WorldObject2d> //Maybe ObjectGroupAction<graphics::WorldObject2d>
{
public:
    PhysicalAction(const std::string &name,
                   const std::string &className,
                   const std::vector<std::string> &bodyNames,
                   const std::function<void(std::shared_ptr<WorldObject2d>)> &function);
    PhysicalAction(const filing::JsonIO &input);
    void onActive() override;

private:
    std::function<void(std::shared_ptr<WorldObject2d>)> _func;
};
} // namespace ample::game::stateMachine::actions
