#pragma once

namespace ample::graphics
{
template <typename T>
struct Vector3d
{
    Vector3d(T xp, T yp, T zp)
        : x(xp), y(yp), z(zp) {}

    Vector3d();

    T x, y, z;
};
} // namespace ample::graphics
