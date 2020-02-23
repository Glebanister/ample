#include <GL/gl.h>
#include <GL/glu.h>

#include "CameraPerspective.h"

namespace ample::graphics
{
CameraPerspective::CameraPerspective(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
                                     Vector2d<double> cameraSize, Vector3d<double> cameraPosition,
                                     double ratio)
    : Camera(viewSize, viewPosition, cameraSize, cameraPosition, ratio)
{
    setPerspective(-cameraSize.x / 2.0, cameraSize.x / 2.0, -cameraSize.y / 2.0, cameraSize.y / 2.0, 1.0, 500);
}

CameraPerspective::CameraPerspective(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
                                     Vector2d<double> cameraSize, Vector2d<double> cameraPosition,
                                     double ratio)
    : CameraPerspective(viewSize, viewPosition, cameraSize, {cameraPosition.x, cameraPosition.y, -1.0}, ratio) {}

CameraPerspective::CameraPerspective(Vector2d<pixel_t> viewSize,
                                     Vector2d<double> cameraSize,
                                     double ratio)
    : CameraPerspective(viewSize, {0, 0}, cameraSize, {0, 0}, ratio) {}

CameraPerspective::CameraPerspective(Vector2d<pixel_t> viewSize, double ratio)
    : CameraPerspective(viewSize, {static_cast<double>(viewSize.x), static_cast<double>(viewSize.y)}, ratio) {}

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
    glClearColor(20.0 / 256.0, 60.0 / 256.0, 80.0 / 256.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(_left, _right,
              _bottom, _top,
              _near, _far);

    glTranslated(_position.x * _ratio,
                 _position.y * _ratio,
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
} // namespace ample::graphics
