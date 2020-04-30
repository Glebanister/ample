#include "Rectangle.h"
#include "JsonIO.h"

namespace ample::geometry
{
Rectangle::Rectangle(const std::pair<graphics::Vector2d<float>, graphics::Vector2d<float>> &rec)
    : Shape("Rectangle"), _r(rec) {}

bool Rectangle::inside(const graphics::Vector2d<float> &crd)
{
    return _r.first.x <= crd.x && crd.x <= _r.second.x &&
           _r.first.y <= crd.x && crd.y <= _r.second.y;
}

Rectangle::Rectangle(const std::string &input)
    : Rectangle({filing::JsonIO(input).read<graphics::Vector2d<float>>("left_bottom"),
                 filing::JsonIO(input).read<graphics::Vector2d<float>>("right_top")})
{
}

std::string Rectangle::dump()
{
    filing::JsonIO result = Shape::dump();
    result.write<graphics::Vector2d<float>>("left_bottom", _r.first);
    result.write<graphics::Vector2d<float>>("right_top", _r.second);
}
} // namespace ample::geometry
