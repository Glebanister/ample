#pragma once

#include "GraphicalAction.h"

/*
Class: GraphicalRotateAction

Rotates all 'bodyNames' an 'angle' along the 'axis'
*/

namespace ample::game::stateMachine::actions
{
class GraphicalRotateAction : public GraphicalAction
{
public:
    GraphicalRotateAction(const std::string &name,
                          const std::vector<std::string> &bodyNames,
                          graphics::Vector3d<float> axis,
                          float angle);

    GraphicalRotateAction(const filing::JsonIO &input);
    std::string dump() override;

    graphics::Vector3d<float> getAxis() const noexcept;
    void setAxis(const graphics::Vector3d<float> &) noexcept;

    float getAngle() const noexcept;
    void setAngle(float) noexcept;

private:
    graphics::Vector3d<float> _axis;
    float _angle;
};
} // namespace ample::game::stateMachine::actions
