#include <cmath>

#include "Circle.h"
#include "Debug.h"
#include "JsonIO.h"

namespace ample::geometry
{
Circle::Circle(const graphics::Vector2d<float> center, float r)
    : Shape("Circle"), _center(center), _r(r) {}

bool Circle::inside(const graphics::Vector2d<float> &crd)
{
    return _r * _r >= (crd.x - _center.x) * (crd.x - _center.x) + (crd.y - _center.y) * (crd.y - _center.y);
}

Circle::Circle(const std::string &input)
    : Circle(filing::JsonIO(input).read<graphics::Vector2d<float>>("center"),
             filing::JsonIO(input).read<float>("radius"))
{
}

std::string Circle::dump()
{
    filing::JsonIO result = Shape::dump();
    result.write<graphics::Vector2d<float>>("center", _center);
    result.write<float>("radius", _r);
    return result;
}
} // namespace ample::geometry
