#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
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
               Vector3d<float> direction)
    : _viewport(viewSize, viewPosition),
      _position(eyePos.x, eyePos.y, eyePos.z),
      _direction(direction.x, direction.y, direction.z)
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

void Camera::translate(const glm::vec3 &vector)
{
    _position += vector;
}

void Camera::rotate(const glm::vec3 &axis, const float angle)
{
    _direction = glm::rotate(_direction, glm::radians(angle), axis);
}

void Camera::moveInViewDirection(float units)
{
    _position += _direction * units;
}
} // namespace ample::graphics
