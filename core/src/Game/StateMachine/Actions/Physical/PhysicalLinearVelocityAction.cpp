#include "PhysicalLinearVelocityAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalLinearVelocityAction::PhysicalLinearVelocityAction(const std::string &name,
                             const std::vector<std::string> &bodyNames,
                             const graphics::Vector2d<float> &newLinearVelocity)
    : PhysicalAction(name,
                      "PhysicalLinearVelocityAction",
                      bodyNames,
                      [newLinearVelocity](std::shared_ptr<physics::WorldObject2d> obj) {
                          obj->setLinearVelocity(newLinearVelocity);
                      }),
      _newLinearVelocity(newLinearVelocity) {}
                        
PhysicalLinearVelocityAction::PhysicalLinearVelocityAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _newLinearVelocity(input.read<graphics::Vector2d<float>>("linear_velocity")) {}

std::string PhysicalLinearVelocityAction::dump() 
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<graphics::Vector2d<float>>("linear_velocity", _newLinearVelocity);
    return result;
}
} // namespace ample::game::stateMachine::actions