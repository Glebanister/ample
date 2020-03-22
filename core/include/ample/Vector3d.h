#pragma once

#include <utility>

namespace ample::graphics
{
template <typename T>
struct Vector3d
{
    Vector3d(T xp, T yp, T zp)
        : x(xp), y(yp), z(zp) {}

    Vector3d()
        : Vector3d(0, 0, 0) {}

    Vector3d &operator+=(const Vector3d &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3d &operator+=(Vector3d &&other)
    {
        x += std::move(other.x);
        y += std::move(other.y);
        z += std::move(other.z);
        return *this;
    }

    Vector3d &operator*=(const double k)
    {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    Vector3d &operator*=(const Vector3d &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    T x, y, z;
};
} // namespace ample::graphics
