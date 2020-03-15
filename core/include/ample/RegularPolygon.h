#pragma once

#include <vector>

#include "Vector2d.h"
#include "Debug.h"

namespace ample::geometry
{
template <typename T>
std::vector<graphics::Vector2d<T>> RegularPolygon(T radius, size_t nVerticies, float startAngle = 0.0)
{
    std::vector<graphics::Vector2d<T>> shape(nVerticies);
    for (size_t i = 0; i < nVerticies; ++i)
    {
        shape[i].x = radius * std::sin(i / (double)nVerticies * M_PI * 2 + startAngle);
        shape[i].y = radius * std::cos(i / (double)nVerticies * M_PI * 2 + startAngle);
    }
    return shape;
}
} // namespace ample::geometry
