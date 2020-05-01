#include "GraphicalTranslateAction.h"

namespace ample::game::stateMachine::actions
{
GraphicalTranslateAction::GraphicalTranslateAction(const std::string &name,
                                                   const std::vector<std::string> &bodyNames,
                                                   graphics::Vector3d<float> direction)
    : GraphicalAction(name,
                      "GraphicalTranslateAction",
                      bodyNames,
                      [direction](std::shared_ptr<graphics::GraphicalObject> obj) {
                          obj->translate({direction.x, direction.y, direction.z});
                      }),
      _direction(direction)
{
}

GraphicalTranslateAction::GraphicalTranslateAction(const filing::JsonIO &input)
    : GraphicalTranslateAction(input.read<std::string>("name"),
                               input.read<std::vector<std::string>>("body_names"),
                               input.read<graphics::Vector3d<float>>("direction"))
{
}

std::string GraphicalTranslateAction::dump()
{
    filing::JsonIO result = GraphicalAction::dump();
    result.write<graphics::Vector3d<float>>("direction", _direction);
    return result;
}
} // namespace ample::game::stateMachine::actions
