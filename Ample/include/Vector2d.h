#pragma once

namespace ample::graphics
{
typedef double pixel_t;

struct Vector2d
{
    Vector2d(pixel_t xp, pixel_t yp);
    Vector2d();

    pixel_t x, y;
};
}