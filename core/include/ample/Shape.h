#pragma once

#include "Vector2d.h"

namespace ample::geometry
{
class Shape
{
public:
    virtual bool inside(const graphics::Vector2d<float> &) = 0;
};
} // namespace ample::Geometry
