#include <GL/gl.h>
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
      _position(cameraPosition) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> cameraPosition, Vector2d<pixel_t> cameraSize,
                           Vector2d<pixel_t> viewportPosition, Vector2d<pixel_t> viewportSize)
    : Camera2d(viewportPosition.x, viewportPosition.y, viewportSize.x, viewportSize.y),
      _size(cameraSize),
      _position(cameraPosition.x, cameraPosition.y, 0.0) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> cameraSize, Vector2d<pixel_t> viewportSizes)
    : Camera2d(viewportSizes.x, viewportSizes.y),
      _size(cameraSize) {}

ScreenCamera::ScreenCamera(Vector2d<pixel_t> viewportSize)
    : ScreenCamera(viewportSize, viewportSize) {}

void ScreenCamera::look()
{
    static bool wasInit = false;
    if (!wasInit)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        wasInit = true;
    }
    _viewport.set();
    glClearColor(0.1, 0.1, 0.1, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, _size.x, _size.y, 0.f, 0.f, 1.f);

    glTranslated(_position.x, _position.y, 0);
    glScaled(_scale.x, _scale.y, _scale.z);
    glRotated(_angle.x, 1.0, 0.0, 0.0);
    glRotated(_angle.y, 0.0, 1.0, 0.0);
    glRotated(_angle.z, 0.0, 0.0, 1.0);
}

void ScreenCamera::unlook()
{
    glPopMatrix();
}

void ScreenCamera::scaleX(double coef)
{
    _scale.x = coef;
}
void ScreenCamera::scaleY(double coef)
{
    _scale.y = coef;
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
    _position.z *= dz;
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
} // namespace ample::graphics
