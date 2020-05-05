#pragma once

#include "Shape.h"
#include "Vector2d.h"

namespace ample::geometry
{
class Point : public Shape
{
public:
    Point(const graphics::Vector2d<float> &);
    Point(const std::string &input);
    std::string dump() override;
    bool inside(const graphics::Vector2d<float> &) override;

private:
    graphics::Vector2d<float> _crd;
};
} // namespace ample::geometry
