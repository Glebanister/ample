#pragma once

namespace ample::graphics
{
template <typename T>
struct Vector2d
{
    Vector2d(T xp, T yp)
        : x(xp), y(yp) {}

    Vector2d()
        : Vector2d(0, 0) {}

    T x, y;
};
} // namespace ample::graphics
