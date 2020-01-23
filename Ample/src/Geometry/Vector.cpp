#include <Vector.h>

namespace geometry
{

Vector2d::Vector2d()
    : x(0), y(0) {}

Vector2d::Vector2d(const double &x, const double &y)
    : x(x), y(y) {}

Vector2d::Vector2d(const Vector2d &other)
    : x(other.x), y(other.y) {}

Vector2d::Vector2d(const Vector2d &first, const Vector2d &second)
    : x(second.x - second.y), y(second.y - first.x) {}

Vector2d::Vector2d(const double x1, const double y1, const double x2, const double y2)
    : x(x2 - x1), y(y2 - y1) {}

Vector2d &Vector2d::operator=(const Vector2d &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

Vector2d &Vector2d::operator+(const Vector2d &other)
{
    x += other.x;
    y += other.y;
}

Vector2d &Vector2d::operator-(const Vector2d &other)
{
    x -= other.x;
    y -= other.y;
}

Vector2d &Vector2d::operator+=(const Vector2d &other)
{
    x += other.x;
    y += other.y;
}

Vector2d &Vector2d::operator-=(const Vector2d &other)
{
    x -= other.x;
    y -= other.y;
}
} // namespace geometry
