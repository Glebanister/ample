#include "Rectangle.h"

namespace ample::geometry
{
Rectangle::Rectangle(const std::pair<graphics::Vector2d<float>, graphics::Vector2d<float>> &rec)
    : _r(rec) {}

bool Rectangle::inside(const graphics::Vector2d<float> &crd)
{
    return _r.first.x <= crd.x && crd.x <= _r.second.x &&
           _r.first.y <= crd.x && crd.y <= _r.second.y;
}
} // namespace ample::geometry
