#include <GL/gl.h>
#include <GL/glu.h>

#include "CameraPerspective.h"

namespace ample::graphics
{
CameraPerspective::CameraPerspective(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView, double ratio)
    : Camera(xView, yView, wView, hView) {}

CameraPerspective::CameraPerspective(pixel_t wView, pixel_t hView, double ratio)
    : Camera(wView, hView, ratio) {}

void CameraPerspective::look()
{
    static bool wasInit = false;
    if (!wasInit)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT | GL_BACK, GL_FILL);
        wasInit = true;
    }
    _viewport.set();
    glClearColor(0.1, 0.1, 0.1, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(_left, _right,
              _bottom, _top,
              _near, _far);

    glTranslated(_position.x * raito,
                 _position.y * raito,
                 _position.z * _ratio);
    glScaled(_scale.x, _scale.y, _scale.z);
    glRotated(_angle.x, 1.0, 0.0, 0.0);
    glRotated(_angle.y, 0.0, 1.0, 0.0);
    glRotated(_angle.z, 0.0, 0.0, 1.0);
}

void CameraPerspective::unlook()
{
    glPopMatrix();
}

double CameraPerspective::getLeft() const
{
    return _left;
}
double CameraPerspective::getRight() const
{
    return _right;
}
double CameraPerspective::getBottom() const
{
    return _bottom;
}
double CameraPerspective::getTop() const
{
    return _top;
}
double CameraPerspective::getNear() const
{
    return _bottom;
}
double CameraPerspective::getFar() const
{
    return _far;
}

void CameraPerspective::setPerspective(double left, double right, double bottom, double top, double near, double far)
{
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
    _near = near;
    _far = far;
}
} // namespace ample::graphics
