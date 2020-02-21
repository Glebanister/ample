#include <GL/gl.h>
#include <GL/glu.h>

#include "Camera2d.h"

namespace ample::graphics
{
Camera2d::Camera2d(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView)
    : Camera(xView, yView, wView, hView) {}

Camera2d::Camera2d(pixel_t wView, pixel_t hView)
    : Camera(wView, hView) {}

void Camera2d::look()
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

    glFrustum(getLeft(), getRight(),
              getBottom(), getTop(),
              getNear(), getFar());

    glTranslated(getX(), getY(), getZ());
    glScaled(getScaleX(), getScaleY(), getScaleZ());
    glRotated(getAngleX(), 1.0, 0.0, 0.0);
    glRotated(getAngleY(), 0.0, 1.0, 0.0);
    glRotated(getAngleZ(), 0.0, 0.0, 1.0);
}

void Camera2d::unlook()
{
    glPopMatrix();
}

} // namespace ample::graphics
