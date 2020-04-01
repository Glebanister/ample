#include <cmath>

#include "Circle.h"
#include "Debug.h"

namespace ample::geometry
{

Circle::Circle(const graphics::Vector2d<float> center, float r)
    : _center(center), _r(r) {}

bool Circle::inside(const graphics::Vector2d<float> &crd)
{
    return _r * _r >= (crd.x - _center.x) * (crd.x - _center.x) + (crd.y - _center.y) * (crd.y - _center.y);
}
} // namespace ample::geometry
