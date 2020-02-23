#include "ScreenObject.h"

namespace ample::graphics
{

ScreenObject::ScreenObject(const std::vector<Vector2d<pixel_t>> &shape, Vector3d<pixel_t> position)
    : GraphicalObject2d(shape), _position(position) {}

ScreenObject::ScreenObject(const std::vector<Vector2d<pixel_t>> &shape)
    : GraphicalObject2d(shape) {}

pixel_t ScreenObject::getX() const
{
    return _position.x;
}
pixel_t ScreenObject::getY() const
{
    return _position.y;
}
pixel_t ScreenObject::getZ() const
{
    return _position.z;
}

radians_t ScreenObject::getAngleX() const
{
    return _angle.x;
}
radians_t ScreenObject::getAngleY() const
{
    return _angle.y;
}
radians_t ScreenObject::getAngleZ() const
{
    return _angle.z;
}

double ScreenObject::getScaleX() const
{
    return _scale.x;
}
double ScreenObject::getScaleY() const
{
    return _scale.y;
}
double ScreenObject::getScaleZ() const
{
    return _scale.z;
}

void ScreenObject::rotateX(radians_t angle)
{
    _angle.x += angle;
}
void ScreenObject::rotateY(radians_t angle)
{
    _angle.y += angle;
}
void ScreenObject::rotateZ(radians_t angle)
{
    _angle.z += angle;
}

void ScreenObject::translateX(pixel_t dx)
{
    _position.x += dx;
}
void ScreenObject::translateY(pixel_t dy)
{
    _position.y += dy;
}
void ScreenObject::translateZ(pixel_t dz)
{
    _position.z += dz;
}

void ScreenObject::scaleX(double coef)
{
    _scale.x *= coef;
}
void ScreenObject::scaleY(double coef)
{
    _scale.y *= coef;
}
void ScreenObject::scaleZ(double coef)
{
    _scale.z *= coef;
}

void ScreenObject::setX(pixel_t x)
{
    _position.x = x;
}

void ScreenObject::setY(pixel_t y)
{
    _position.y = y;
}

void ScreenObject::setZ(pixel_t z)
{
    _position.z = z;
}
} // namespace ample::graphics
