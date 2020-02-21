#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "ScreenCamera.h"
#include "Camera.h"
#include "Vector2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
ScreenCamera::ScreenCamera(Vector3d<pixel_t> cameraPosition, Vector2d<pixel_t> cameraSize,
                           Vector2d<pixel_t> viewportPosition, Vector2d<pixel_t> viewportSize)
    : Camera2d(viewportPosition.x, viewportPosition.y, viewportSize.x, viewportSize.y),
      _size(cameraSize),
      _position(cameraPosition),
      _camLeft(-_size.x / 2), _camRight(_size.x / 2),
      _camBot(-_size.y / 2), _camTop(_size.y / 2),
      _camNear(1.0), _camFar(500.0) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> cameraPosition, Vector2d<pixel_t> cameraSize,
                           Vector2d<pixel_t> viewportPosition, Vector2d<pixel_t> viewportSize)
    : ScreenCamera({cameraPosition.x, cameraPosition.y, 0.0}, cameraSize,
                   viewportPosition, viewportSize) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> cameraSize, Vector2d<pixel_t> viewportSize)
    : ScreenCamera({0.0, 0.0, 0.0}, cameraSize, {0.0, 0.0}, viewportSize) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> viewportSize)
    : ScreenCamera(viewportSize, viewportSize) {}

void ScreenCamera::scaleX(double coef)
{
    _scale.x *= coef;
}
void ScreenCamera::scaleY(double coef)
{
    _scale.y *= coef;
}
void ScreenCamera::scaleZ(double coef)
{
    _scale.z *= coef;
}

void ScreenCamera::translateX(pixel_t dx)
{
    _position.x += dx;
}
void ScreenCamera::translateY(pixel_t dy)
{
    _position.y += dy;
}
void ScreenCamera::translateZ(pixel_t dz)
{
    _position.z += dz;
}

void ScreenCamera::rotateX(radians_t angle)
{
    _angle.x += angle;
}
void ScreenCamera::rotateY(radians_t angle)
{
    _angle.y += angle;
}
void ScreenCamera::rotateZ(radians_t angle)
{
    _angle.z += angle;
}

double ScreenCamera::getScaleX() const
{
    return _scale.x;
}
double ScreenCamera::getScaleY() const
{
    return _scale.y;
}
double ScreenCamera::getScaleZ() const
{
    return _scale.z;
}

pixel_t ScreenCamera::getX() const
{
    return _position.x;
}
pixel_t ScreenCamera::getY() const
{
    return _position.y;
}
pixel_t ScreenCamera::getZ() const
{
    return _position.z;
}

radians_t ScreenCamera::getAngleX() const
{
    return _angle.x;
}
radians_t ScreenCamera::getAngleY() const
{
    return _angle.y;
}
radians_t ScreenCamera::getAngleZ() const
{
    return _angle.z;
}

pixel_t ScreenCamera::getLeft() const
{
    return _camLeft;
}
pixel_t ScreenCamera::getRight() const
{
    return _camRight;
}
pixel_t ScreenCamera::getBottom() const
{
    return _camBot;
}
pixel_t ScreenCamera::getTop() const
{
    return _camTop;
}
pixel_t ScreenCamera::getNear() const
{
    return _camNear;
}
pixel_t ScreenCamera::getFar() const
{
    return _camFar;
}

void ScreenCamera::setCameraProperties(pixel_t left, pixel_t right,
                                       pixel_t bottom, pixel_t top,
                                       pixel_t near, pixel_t far)
{
    _camLeft = left;
    _camRight = right;
    _camBot = bottom;
    _camTop = top;
    _camNear = near;
    _camFar = far;
}
} // namespace ample::graphics
