#include <GL/gl.h>
#include <iostream>

#include "Camera.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv)
    : size(wv, hv), position(xv, yv) {}

Camera::Viewport::Viewport(pixel_t wv, pixel_t hv)
    : Viewport(0, 0, wv, hv) {}

void Camera::Viewport::set()
{
    glViewport(position.x, position.y, size.x, size.y);
}

Camera::Camera(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
               Vector2d<double> cameraSize, Vector3d<double> cameraPosition,
               double ratio)
    : _viewport(viewPosition.x, viewPosition.y, viewSize.x, viewSize.y),
      _size(cameraSize), _position(cameraPosition), _ratio(ratio) {}

Camera::Camera(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
               Vector2d<double> cameraSize, Vector2d<double> cameraPosition,
               double ratio)
    : Camera(viewSize, viewPosition, cameraSize, {cameraPosition.x, cameraPosition.y, 0}, ratio) {}

Camera::Camera(Vector2d<pixel_t> viewSize,
               Vector2d<double> cameraSize,
               double ratio)
    : Camera(viewSize, {0, 0}, cameraSize, {0, 0}, ratio) {}

Camera::Camera(Vector2d<pixel_t> cameraSize, double ratio)
    : Camera(cameraSize, {static_cast<double>(cameraSize.x), static_cast<double>(cameraSize.y)}, ratio) {}

void Camera::setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h)
{
    _viewport.position.x = x;
    _viewport.position.y = y;
    _viewport.size.x = w;
    _viewport.size.y = h;
}
void Camera::setViewport(pixel_t w, pixel_t h)
{
    setViewport(0, 0, w, h);
}

void Camera::setRatio(double ratio)
{
    _ratio = ratio;
}

void Camera::scale(double x, double y, double z)
{
    _scale.x *= x;
    _scale.y *= y;
    _scale.z *= z;
}
void Camera::translate(double x, double y, double z)
{
    _position.x += x;
    _position.y += y;
    _position.z += z;
}
void Camera::rotate(double x, double y, double z)
{
    _angle.x += x;
    _angle.y += y;
    _angle.z += z;
}

void Camera::scaleSet(double x, double y, double z)
{
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
}
void Camera::translateSet(double x, double y, double z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}
void Camera::rotateSet(double x, double y, double z)
{
    _angle.x = x;
    _angle.y = y;
    _angle.z = z;
}

double Camera::getScaleX() const
{
    return _angle.x;
}
double Camera::getScaleY() const
{
    return _angle.y;
}
double Camera::getScaleZ() const
{
    return _angle.z;
}

double Camera::getX() const
{
    return _position.x;
}
double Camera::getY() const
{
    return _position.y;
}
double Camera::getZ() const
{
    return _position.y;
}
double Camera::getAngleX() const
{
    return _angle.x;
}
double Camera::getAngleY() const
{
    return _angle.y;
}
double Camera::getAngleZ() const
{
    return _angle.z;
}

pixel_t Camera::getViewportX() const
{
    return _viewport.position.x;
}
pixel_t Camera::getViewportY() const
{
    return _viewport.position.y;
}
pixel_t Camera::getViewportW() const
{
    return _viewport.size.x;
}
pixel_t Camera::getViewportH() const
{
    return _viewport.size.y;
}

double Camera::getWidth() const
{
    return _size.x;
}
double Camera::getHeight() const
{
    return _size.y;
}
double Camera::getLeft() const
{
    return _left;
}
double Camera::getRight() const
{
    return _right;
}
double Camera::getBottom() const
{
    return _bottom;
}
double Camera::getTop() const
{
    return _top;
}
double Camera::getNear() const
{
    return _bottom;
}
double Camera::getFar() const
{
    return _far;
}

void Camera::setPerspective(double left, double right, double bottom, double top, double near, double far)
{
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
    _near = near;
    _far = far;
}
} // namespace ample::graphics
