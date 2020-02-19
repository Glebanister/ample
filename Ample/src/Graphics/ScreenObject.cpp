#include "ScreenObject.h"

namespace ample::graphics
{

ScreenObject::ScreenObject(const std::vector<Vector2d> &shape)
    : GraphicalObject2d(shape) {}

pixel_t ScreenObject::getX() const
{
    return _position.x;
}

pixel_t ScreenObject::getY() const
{
    return _position.y;
}

double ScreenObject::getAngle() const
{
    return _angle;
}

double ScreenObject::getScaleX() const
{
    return _scaleX;
}

double ScreenObject::getScaleY() const
{
    return _scaleY;
}
} // namespace ample::graphics
