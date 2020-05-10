#include "PhysicalAngularVelocityAction.h"

namespace ample::game::stateMachine::actions
{
PhysicalAngularVelocityAction::PhysicalAngularVelocityAction(const std::string &name,
                                                             const std::vector<std::string> &bodyNames,
                                                             float angularVelocity)
    : PhysicalAction(name,
                     "PhysicalAngularVelocityAction",
                     bodyNames,
                     [angularVelocity](std::shared_ptr<physics::WorldObject2d> obj) {
                         obj->setAngularVelocity(angularVelocity);
                     }),
      _angularVelocity(angularVelocity) {}

PhysicalAngularVelocityAction::PhysicalAngularVelocityAction(const filing::JsonIO &input)
    : PhysicalAction(input),
      _angularVelocity(input.read<float>("angular_valocity")) {}

std::string PhysicalAngularVelocityAction::dump()
{
    filing::JsonIO result = PhysicalAction::dump();
    result.write<float>("angular_valocity", _angularVelocity);
    return result;
}
} // namespace ample::game::stateMachine::actions