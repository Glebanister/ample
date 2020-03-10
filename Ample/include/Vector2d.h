#pragma once

#include <utility>

namespace ample::graphics
{
template <typename T>
struct Vector2d
{
    Vector2d(T xp, T yp)
        : x(xp), y(yp) {}

    Vector2d()
        : Vector2d(0, 0) {}

    Vector2d &operator+=(const Vector2d &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2d &operator+=(Vector2d &&other)
    {
        x += std::move(other.x);
        y += std::move(other.y);
        return *this;
    }

    Vector2d &operator*=(const double k)
    {
        x *= k;
        y *= k;
        return *this;
    }

    Vector2d &operator*=(const Vector2d &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    T x, y;
};
} // namespace ample::graphics
