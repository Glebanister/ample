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

Camera::Camera(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView, double ratio)
    : _viewport(xView, yView, wView, hView), _ratio(ratio) {}

Camera::Camera(pixel_t wView, pixel_t hView, double ratio)
    : Camera(0, 0, wView, hView, ratio) {}

void Camera::setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h)
{
    _viewport = Viewport(x, y, w, h);
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
    _position.x *= x;
    _position.y *= y;
    _position.z *= z;
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
} // namespace ample::graphics
