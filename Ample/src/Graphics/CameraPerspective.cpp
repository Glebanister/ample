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
    setPerspective(-cameraSize.x / 2.0, cameraSize.x / 2.0, -cameraSize.y / 2.0, cameraSize.y / 2.0, 1000.0, 20000.0);
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
    _viewport.set();
    glPushMatrix();
    glFrustum(_left, _right,
              _bottom, _top,
              _near, _far);
    glScaled(_scale.x, _scale.y, _scale.z);
    glTranslated(_position.x * _ratio,
                 _position.y * _ratio,
                 _position.z * _ratio);
    glRotated(_angle.x, 1.0, 0.0, 0.0);
    glRotated(_angle.y, 0.0, 1.0, 0.0);
    glRotated(_angle.z, 0.0, 0.0, 1.0);
}

void CameraPerspective::unlook()
{
    glPopMatrix();
}
} // namespace ample::graphics
