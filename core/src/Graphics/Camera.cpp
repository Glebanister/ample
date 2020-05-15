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

Camera::Camera(const std::string &name,
               const std::string &className,
               Vector2d<pixel_t> viewSize,
               Vector2d<pixel_t> viewPosition,
               Vector3d<float> eyePos,
               Vector3d<float> direction)
    : NamedStoredObject(name, className),
      _viewport(viewSize, viewPosition),
      _position(eyePos.x, eyePos.y, eyePos.z),
      _direction(direction.x, direction.y, direction.z)
{
}

std::string Camera::dump()
{
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<Vector2d<pixel_t>>("view_size", _viewport.size);
    output.write<Vector2d<pixel_t>>("view_position", _viewport.position);
    output.write<Vector3d<float>>("eye_pos", {_position.x, _position.y, _position.z});
    output.write<Vector3d<float>>("eye_dir", {_direction.x, _direction.y, _direction.z});
    return output;
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

void Camera::setTranslate(const glm::vec3 &vector)
{
    _position = vector;
}

void Camera::rotate(const glm::vec3 &axis, const float angle)
{
    _direction = glm::rotate(_direction, glm::radians(angle), axis);
    _head = glm::rotate(_head, glm::radians(angle), axis);
    _right = glm::rotate(_right, glm::radians(angle), axis);
}

void Camera::moveForward(float units)
{
    _position += _direction * units;
}
void Camera::moveRight(float units)
{
    _position -= _right * units;
}
void Camera::moveUp(float units)
{
    _position += _head * units;
}

void Camera::rotateForward(float angle)
{
    rotate(_direction, angle);
}
void Camera::rotateRight(float angle)
{
    rotate({0.0, 1.0, 0.0}, -angle);
}
void Camera::rotateUp(float angle)
{
    rotate(_right, -angle);
}

void Camera::setVisibility(const bool value)
{
    _visible = value;
}
bool Camera::visible() const noexcept
{
    return _visible;
}

float Camera::getX() const noexcept
{
    return _position.x;
}
float Camera::getY() const noexcept
{
    return _position.y;
}
float Camera::getZ() const noexcept
{
    return _position.z;
}
} // namespace ample::graphics
