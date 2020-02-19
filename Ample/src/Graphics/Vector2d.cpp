#include "Vector2d.h"

namespace ample::graphics
{
Vector2d::Vector2d(pixel_t xp, pixel_t yp)
    : x(xp), y(yp) {}

Vector2d::Vector2d()
    : Vector2d(0.0, 0.0) {}
} // namespace ample::graphics
