#include "Point.h"

namespace ample::geometry
{
Point::Point(const graphics::Vector2d<float> &crd)
    : _crd(crd) {}

bool Point::inside(const graphics::Vector2d<float> &crd)
{
    return crd.x == _crd.x && crd.y == _crd.y;
}
} // namespace ample::geometry
