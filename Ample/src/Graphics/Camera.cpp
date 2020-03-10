#include <GL/gl.h>
#include <iostream>

#include "Camera.h"
#include "Debug.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(Vector2d<pixel_t> viewportSize, Vector2d<pixel_t> viewportPos)
    : size(viewportSize), position(viewportPos) {}

void Camera::Viewport::set()
{
    glViewport(position.x, position.y, size.x, size.y);
}

Camera::Camera(Vector2d<pixel_t> viewSize,
               Vector2d<pixel_t> viewPosition,
               Vector3d<float> eyePos,
               Vector3d<float> targetPos,
               float ratio)
    : _viewport(viewSize, viewPosition), _position(eyePos), _target(targetPos), _ratio(ratio)
{
}

void Camera::setViewport(Vector2d<pixel_t> &&size, Vector2d<pixel_t> &&pos)
{
    _viewport.position = std::move(pos);
    _viewport.size = std::move(size);
}

void Camera::setViewport(const Vector2d<pixel_t> &size, const Vector2d<pixel_t> &pos)
{
    _viewport.position = pos;
    _viewport.size = size;
}

void Camera::setViewport(Vector2d<pixel_t> &&size)
{
    setViewport(Vector2d<pixel_t>{0, 0}, std::move(size));
}

void Camera::setViewport(const Vector2d<pixel_t> &size)
{
    setViewport(Vector2d<pixel_t>{0, 0}, size);
}

void Camera::setRatio(float ratio)
{
    _ratio = ratio;
}

float Camera::getRatio() const
{
    return _ratio;
}

void Camera::translateEye(Vector3d<float> &&vector)
{
    _position += std::move(vector);
}

void Camera::translateEye(const Vector3d<float> &vector)
{
    _position += vector;
}

void Camera::rotateHead(Vector3d<float> &&angles)
{
    DEBUG("STUB for camera head rotation");
}

void Camera::rotateHead(const Vector3d<float> &angles)
{
    DEBUG("STUB for camera head rotation");
}

void Camera::setEyeTranslated(Vector3d<float> &&position)
{
    _position = std::move(position);
}

void Camera::setEyeTranslated(const Vector3d<float> &position)
{
    _position = position;
}

void Camera::setHeadRotated(Vector3d<float> &&)
{
    DEBUG("STUB for camera set head rotation");
}

void Camera::setHeadRotated(const Vector3d<float> &)
{
    DEBUG("STUB for camera set head rotation");
}

float Camera::getEyeX() const
{
    return _position.x;
}
float Camera::getEyeY() const
{
    return _position.y;
}
float Camera::getEyeZ() const
{
    return _position.z;
}

float Camera::getHeadAngleX() const
{
    DEBUG("STUB for camera getAngleX()");
    return _angle.x;
}
float Camera::getHeadAngleY() const
{
    DEBUG("STUB for camera getAngleY()");
    return _angle.y;
}
float Camera::getHeadAngleZ() const
{
    DEBUG("STUB for camera getAngleZ()");
    return _angle.z;
}

void Camera::setTarget(Vector3d<float> &&target)
{
    _target = std::move(target);
}

void Camera::setTarget(const Vector3d<float> &target)
{
    _target = target;
}

void Camera::translateTarget(Vector3d<float> &&vector)
{
    _target += std::move(vector);
}

void Camera::translateTarget(const Vector3d<float> &vector)
{
    _target += vector;
}

void Camera::translate(Vector3d<float> &&vector)
{
    _target += std::move(vector);
    _position += std::move(vector);
}

void Camera::translate(const Vector3d<float> &vector)
{
    _target += vector;
    _position += vector;
}
} // namespace ample::graphics
