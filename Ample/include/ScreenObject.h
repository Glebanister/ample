#pragma once

#include <vector>

#include "GraphicalObject2d.h"
#include "Vector2d.h"

namespace ample::graphics
{
class ScreenObject : public GraphicalObject2d
{
public:
    ScreenObject(const std::vector<Vector2d> &);
    pixel_t getX() const override;
    pixel_t getY() const override;
    double getAngle() const override;
    double getScaleX() const override;
    double getScaleY() const override;

protected:
    Vector2d _position;
    double _angle = 0.0;
    double _scaleX = 1.0, _scaleY = 1.0;
};
} // namespace ample::graphics
