#include <GL/gl.h>
#include <iostream>

#include "Camera.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv)
    : x(xv), y(yv), w(wv), h(hv) {}

Camera::Viewport::Viewport(pixel_t wv, pixel_t hv)
    : Viewport(0, 0, wv, hv) {}

void Camera::Viewport::set()
{
    glViewport(x, y, w, h);
}

void Camera::setViewport(const Viewport &viewport)
{
    _viewport = viewport;
}

void Camera::setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h)
{
    _viewport = Viewport(x, y, w, h);
}

void Camera::setViewport(pixel_t w, pixel_t h)
{
    _viewport = Viewport(w, h);
}
} // namespace ample::graphics
