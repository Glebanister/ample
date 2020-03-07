#include "ScreenObject.h"

namespace ample::graphics
{
ScreenObject::ScreenObject(const std::vector<Vector2d<float>> &shape, Vector3d<float> position)
    : GraphicalObject2d(shape), _position(position) {}

ScreenObject::ScreenObject(const std::vector<Vector2d<float>> &shape, Vector2d<float> position)
    : GraphicalObject2d(shape), _position(position.x, _position.y, 0.0) {}

float ScreenObject::getX() const
{
    return _position.x;
}
float ScreenObject::getY() const
{
    return _position.y;
}
float ScreenObject::getZ() const
{
    return _position.z;
}

float ScreenObject::getAngleX() const
{
    return _angle.x;
}
float ScreenObject::getAngleY() const
{
    return _angle.y;
}
float ScreenObject::getAngleZ() const
{
    return _angle.z;
}

float ScreenObject::getScaleX() const
{
    return _scale.x;
}
float ScreenObject::getScaleY() const
{
    return _scale.y;
}
float ScreenObject::getScaleZ() const
{
    return _scale.z;
}

void ScreenObject::rotate(Vector3d<float> angle)
{
    _angle += angle;
}

void ScreenObject::translate(Vector3d<float> vector)
{
    _position += vector;
}

void ScreenObject::scale(Vector3d<float> scale)
{
    _scale *= scale;
}

void ScreenObject::setRotate(Vector3d<float> angle)
{
    _angle = angle;
}

void ScreenObject::setTranslate(Vector3d<float> vector)
{
    _position = vector;
}

void ScreenObject::setScale(Vector3d<float> scale)
{
    _scale = scale;
}

} // namespace ample::graphics
