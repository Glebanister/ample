#include "GraphicalTranslateAction.h"

namespace ample::game::stateMachine::actions
{
GraphicalTranslateAction::GraphicalTranslateAction(const std::string &name,
                                                   const std::vector<std::string> &bodyNames,
                                                   graphics::Vector3d<float> direction)
    : GraphicalAction(name,
                      "GraphicalTranslateAction",
                      bodyNames),
      _direction(direction)
{
}

GraphicalTranslateAction::GraphicalTranslateAction(const filing::JsonIO &input)
    : GraphicalTranslateAction(input.read<std::string>("name"),
                               input.read<std::vector<std::string>>("body_names"),
                               input.read<graphics::Vector3d<float>>("direction"))
{
}

void GraphicalTranslateAction::onActive()
{
    GraphicalAction::onActive();
    for (const auto &obj : bodyPointers())
    {
        obj->translate({_direction.x, _direction.y, _direction.z});
    }
}

std::string GraphicalTranslateAction::dump()
{
    filing::JsonIO result = GraphicalAction::dump();
    result.write<graphics::Vector3d<float>>("direction", _direction);
    return result;
}
} // namespace ample::game::stateMachine::actions
