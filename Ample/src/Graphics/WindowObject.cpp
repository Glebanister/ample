#include "WindowObject.h"
#include "Utils.h"

namespace graphics
{
WindowObject2d::WindowObject2d()
    : pos() {}

WindowObject2d::WindowObject2d(const geometry::Vector2d &pos)
    : pos(pos) {}

void WindowObject2d::translate(const double &dx, const double &dy)
{
    geometry::Vector2d delta(dx, dy);
    this->pos += delta;
}

void WindowObject2d::translate(const geometry::Vector2d &vector)
{
    this->pos += vector;
}

void WindowObject2d::rotate(const double &rotAngle)
{
    this->angle += rotAngle;
}

void WindowObject2d::scale(const double &scaleCoef)
{
    this->scaleDegree += scaleCoef;
}

} // namespace graphics
