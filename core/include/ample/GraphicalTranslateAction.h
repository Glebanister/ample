#pragma once

#include "GraphicalAction.h"

/*
Class: GraphicalTranslateAction

Translates all 'bodyNames' in 'direction'
*/

namespace ample::game::stateMachine::actions
{
class GraphicalTranslateAction : public GraphicalAction
{
public:
    GraphicalTranslateAction(const std::string &name,
                             const std::vector<std::string> &bodyNames,
                             graphics::Vector3d<float> direction);

    GraphicalTranslateAction(const filing::JsonIO &input);
    std::string dump() override;

private:
    graphics::Vector3d<float> _direction;
};
} // namespace ample::game::stateMachine::actions
