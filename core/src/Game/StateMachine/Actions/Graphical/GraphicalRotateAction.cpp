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

graphics::Vector3d<float> GraphicalRotateAction::getAxis() const noexcept
{
    return _axis;
}

void GraphicalRotateAction::setAxis(const graphics::Vector3d<float> &axis) noexcept
{
    _axis = axis;
}

float GraphicalRotateAction::getAngle() const noexcept
{
    return _angle;
}
void GraphicalRotateAction::setAngle(float angle) noexcept
{
    _angle = angle;
}

std::string GraphicalRotateAction::dump()
{
    filing::JsonIO result = GraphicalAction::dump();
    result.write<graphics::Vector3d<float>>("axis", _axis);
    result.write<float>("angle", _angle);
    return result;
}
} // namespace ample::game::stateMachine::actions
