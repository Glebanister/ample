#pragma once

namespace geometry
{
struct Vector2d
{
    Vector2d();

    Vector2d(const double &x, const double &y);

    Vector2d(const Vector2d &other);

    Vector2d(const Vector2d &first, const Vector2d &second);

    Vector2d(const double x1, const double y1, const double x2, const double y2);

    Vector2d &operator=(const Vector2d &other);

    Vector2d &operator+(const Vector2d &other);

    Vector2d &operator-(const Vector2d &other);

    Vector2d &operator+=(const Vector2d &other);

    Vector2d &operator-=(const Vector2d &other);

    double x, y;
};
} // namespace geometry
