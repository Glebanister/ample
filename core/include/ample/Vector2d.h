#pragma once

#include <utility>
#include <cmath>

#include "box2d/b2_math.h"

namespace ample::graphics
{
template <typename T>
struct Vector2d
{
    Vector2d(T xp, T yp)
        : x(xp), y(yp) {}

    Vector2d()
        : Vector2d(0, 0) {}

    Vector2d(const Vector2d &first, const Vector2d second)
        : Vector2d(second.x - first.x, second.y - first.y) {}

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

template <>
struct Vector2d<float>
{
    Vector2d(float xp, float yp)
        : x(xp), y(yp) {}

    Vector2d()
        : Vector2d(0, 0) {}

    Vector2d(const Vector2d &first, const Vector2d second)
        : Vector2d(second.x - first.x, second.y - first.y) {}

    Vector2d(const b2Vec2 &src)
        : Vector2d(src.x, src.y) {}

    operator b2Vec2()
    {
        return {x, y};
    }

    float len() const noexcept
    {
        return sqrt(x * x + y * y);
    }

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

    float x, y;
};
} // namespace ample::graphics
