#include <GL/gl.h>
#include <iostream>

#include "Camera.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv)
    : x(xv), y(yv), w(wv), h(hv) {}

Camera::Viewport::Viewport(pixel_t wv, pixel_t hv)
    : Viewport(0, 0, wv, hv) {}

Camera::Camera(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView)
    : _viewport(xView, yView, wView, hView) {}

Camera::Camera(pixel_t wView, pixel_t hView)
    : _viewport(wView, hView) {}

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

pixel_t Camera::getViewportX() const
{
    return _viewport.x;
}

pixel_t Camera::getViewportY() const
{
    return _viewport.y;
}

pixel_t Camera::getViewportW() const
{
    return _viewport.w;
}

pixel_t Camera::getViewportH() const
{
    return _viewport.h;
}
} // namespace ample::graphics
