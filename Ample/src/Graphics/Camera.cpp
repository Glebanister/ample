#include <GL/gl.h>
#include <iostream>

#include "Camera.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv)
    : x(xv), y(yv), w(wv), h(hv) {}

Camera::Viewport::Viewport()
    : Viewport(0, 0, 0, 0) {}

void Camera::Viewport::set()
{
    glViewport(x, y, w, h);
    std::cout << x << ' ' << y << ' ' << w << ' ' << h << std::endl;
}

void Camera::setViewport(const Viewport &viewport)
{
    _viewport = viewport;
}
} // namespace ample::graphics
