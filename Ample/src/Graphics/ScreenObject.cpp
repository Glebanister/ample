#include "ScreenObject.h"

namespace ample::graphics
{

ScreenObject::ScreenObject(const std::vector<Vector2d<pixel_t>> &shape, Vector3d<double> position)
    : _position(position)
{
    _graphicalShape.resize(shape.size());
    for (size_t i = 0; i < shape.size(); ++i)
    {
        _graphicalShape[i].x = shape[i].x;
        _graphicalShape[i].y = shape[i].y;
    }
}

ScreenObject::ScreenObject(const std::vector<Vector2d<pixel_t>> &shape, Vector2d<double> position)
    : ScreenObject(shape, {position.x, position.y, 0}) {}

ScreenObject::ScreenObject(const std::vector<Vector2d<pixel_t>> &shape)
    : ScreenObject(shape, {0, 0, 0}) {}

double ScreenObject::getX() const
{
    return _position.x;
}
double ScreenObject::getY() const
{
    return _position.y;
}
double ScreenObject::getZ() const
{
    return _position.z;
}

double ScreenObject::getAngleX() const
{
    return _angle.x;
}
double ScreenObject::getAngleY() const
{
    return _angle.y;
}
double ScreenObject::getAngleZ() const
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

void ScreenObject::rotate(radian_t x, radian_t y, radian_t z)
{
    _angle.x += x;
    _angle.y += y;
    _angle.z += z;
}

void ScreenObject::translate(double x, double y, double z)
{
    _position.x += x;
    _position.y += y;
    _position.z += z;
}

void ScreenObject::scale(double x, double y, double z)
{
    _scale.x *= x;
    _scale.y *= y;
    _scale.z *= z;
}

void ScreenObject::setAngle(radian_t x, radian_t y, radian_t z)
{
    _angle.x = x;
    _angle.y = y;
    _angle.z = z;
}

void ScreenObject::setPosition(double x, double y, double z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}

void ScreenObject::setScale(double x, double y, double z)
{
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
}

} // namespace ample::graphics
