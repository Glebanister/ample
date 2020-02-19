#include "Camera2d.h"

namespace ample::graphics
{
Camera2d::Camera2d(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView)
    : Camera(xView, yView, wView, hView) {}

Camera2d::Camera2d(pixel_t wView, pixel_t hView)
    : Camera(wView, hView) {}
} // namespace ample::graphics
