#pragma once

#include <tuple>

#include "Shape.h"
#include "Vector2d.h"

namespace ample::geometry
{
class Rectangle : public Shape
{
public:
    Rectangle(const std::pair<graphics::Vector2d<float>, graphics::Vector2d<float>> &);
    bool inside(const graphics::Vector2d<float> &) override;

private:
    std::pair<graphics::Vector2d<float>, graphics::Vector2d<float>> _r;
};
} // namespace ample::geometry
