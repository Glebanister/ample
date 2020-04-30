#include "Point.h"
#include "JsonIO.h"

namespace ample::geometry
{
Point::Point(const graphics::Vector2d<float> &crd)
    : Shape("Point"), _crd(crd) {}

bool Point::inside(const graphics::Vector2d<float> &crd)
{
    return crd.x == _crd.x && crd.y == _crd.y;
}

Point::Point(const std::string &input)
    : Point(filing::JsonIO(input).read<graphics::Vector2d<float>>("position"))
{
}

std::string Point::dump()
{
    filing::JsonIO result = Shape::dump();
    result.write<graphics::Vector2d<float>>("position", _crd);
}
} // namespace ample::geometry
