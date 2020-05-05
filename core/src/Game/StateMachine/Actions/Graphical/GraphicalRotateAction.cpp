#include "GraphicalRotateAction.h"

namespace ample::game::stateMachine::actions
{
GraphicalRotateAction::GraphicalRotateAction(const std::string &name,
                                             const std::vector<std::string> &bodyNames,
                                             graphics::Vector3d<float> axis,
                                             float angle)
    : GraphicalAction(name,
                      "GraphicalRotateAction",
                      bodyNames,
                      [axis, angle](std::shared_ptr<graphics::GraphicalObject> obj) {
                          obj->rotate({axis.x, axis.y, axis.z}, angle);
                      }),
      _axis(axis),
      _angle(angle)
{
}

GraphicalRotateAction::GraphicalRotateAction(const filing::JsonIO &input)
    : GraphicalRotateAction(input.read<std::string>("name"),
                            input.read<std::vector<std::string>>("body_names"),
                            input.read<graphics::Vector3d<float>>("axis"),
                            input.read<float>("angle"))
{
}

std::string GraphicalRotateAction::dump()
{
    filing::JsonIO result = GraphicalAction::dump();
    result.write<graphics::Vector3d<float>>("axis", _axis);
    result.write<float>("angle", _angle);
    return result;
}
} // namespace ample::game::stateMachine::actions
