#include <GL/gl.h>
#include <iostream>

#include "Camera.h"

namespace ample::graphics
{
Camera::Viewport::Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv)
    : position(xv, yv), size(wv, hv) {}

Camera::Viewport::Viewport(pixel_t wv, pixel_t hv)
    : Viewport(0, 0, wv, hv) {}

Camera::Camera(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView)
    : _viewport(xView, yView, wView, hView) {}

Camera::Camera(pixel_t wView, pixel_t hView)
    : _viewport(wView, hView) {}

void Camera::Viewport::set()
{
    glViewport(position.x, position.y,
               position.x, position.y);
}

void Camera::setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h)
{
    _viewport.position.x = x;
    _viewport.position.y = y;
    _viewport.size.x = w;
    _viewport.size.y = h;
}

void Camera::setViewport(pixel_t w, pixel_t h)
{
    setViewport(0, 0, w, h);
}

pixel_t Camera::getViewportX() const
{
    return _viewport.position.x;
}

pixel_t Camera::getViewportY() const
{
    return _viewport.position.y;
}

pixel_t Camera::getViewportW() const
{
    return _viewport.size.x;
}

pixel_t Camera::getViewportH() const
{
    return _viewport.size.y;
}
} // namespace ample::graphics
