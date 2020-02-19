#include <GL/gl.h>
#include <iostream>

#include "ScreenCamera.h"
#include "Camera.h"
#include "Vector2d.h"

namespace ample::graphics
{

ScreenCamera::ScreenCamera(Vector2d camPos, Vector2d camSizes,
                           Vector2d viewportPos, Vector2d viewportSizes)
    : Camera2d(viewportPos.x, viewportPos.y, viewportSizes.x, viewportSizes.y),
      _camSizes(camSizes), _camPos(camPos) {}

ScreenCamera::ScreenCamera(Vector2d camSizes, Vector2d viewportSizes)
    : Camera2d(viewportSizes.x, viewportSizes.y),
      _camSizes(camSizes) {}

ScreenCamera::ScreenCamera(Vector2d viewportSizes)
    : ScreenCamera(viewportSizes, viewportSizes) {}

void ScreenCamera::look()
{
    static bool wasInit = false;
    if (!wasInit)
    {
        // setViewport(Viewport{0, 0, _width, _height});
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
    glOrtho(0.f, _camSizes.x, _camSizes.y, 0.f, 0.f, 1.f);

    glTranslated(_camPos.x, _camPos.y, 0);
    glScaled(_scaleX, _scaleY, 1.0);
    glRotated(_angle, 0.0, 0.0, 1.0);
}

void ScreenCamera::unlook()
{
    glPopMatrix();
}

void ScreenCamera::scaleX(double coef)
{
    _scaleX *= coef;
}

void ScreenCamera::scaleY(double coef)
{
    _scaleY *= coef;
}

void ScreenCamera::translateX(pixel_t dx)
{
    _camPos.x += dx;
}

void ScreenCamera::translateY(double dy)
{
    _camPos.y += dy;
}

void ScreenCamera::rotateZ(double angle)
{
    _angle += angle;
}

double ScreenCamera::getScaleX() const
{
    return _scaleX;
}

double ScreenCamera::getScaleY() const
{
    return _scaleY;
}

pixel_t ScreenCamera::getX() const
{
    return _camPos.x;
}

pixel_t ScreenCamera::getY() const
{
    return _camPos.y;
}

double ScreenCamera::getAngleZ() const
{
    return _angle;
}
} // namespace ample::graphics
