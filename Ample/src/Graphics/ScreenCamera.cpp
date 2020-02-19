#include <GL/gl.h>
#include <iostream>

#include "ScreenCamera.h"
#include "Vector2d.h"

namespace ample::graphics
{

ScreenCamera::ScreenCamera(Vector2d position, pixel_t width, pixel_t height)
    : _position(position), _width(width), _height(height) {}

ScreenCamera::ScreenCamera(pixel_t width, pixel_t height)
    : ScreenCamera({0.0, 0.0}, width, height) {}

void ScreenCamera::look()
{
    static bool wasInit = false;
    if (!wasInit)
    {
        // setViewport(Viewport{0, 0, _width, _height});
        // _viewport.set();
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        wasInit = true;
    }
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, _width, _height, 0.f, 0.f, 1.f);

    glScaled(_scaleX, _scaleY, 1.0);
    glRotated(_angle, 0.0, 0.0, 1.0);
    glTranslated(_position.x, _position.y, 0);
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
    _position.x += dx;
}

void ScreenCamera::translateY(double dy)
{
    _position.y += dy;
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
    return _position.x;
}

pixel_t ScreenCamera::getY() const
{
    return _position.y;
}

double ScreenCamera::getAngleZ() const
{
    return _angle;
}
} // namespace ample::graphics
