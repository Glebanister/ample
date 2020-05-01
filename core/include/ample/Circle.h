#pragma once

#include "Shape.h"
#include "Vector2d.h"

namespace ample::geometry
{
class Circle : public Shape
{
public:
    Circle(const graphics::Vector2d<float> center, float r);
    bool inside(const graphics::Vector2d<float> &) override;

    Circle(const std::string &input);
    std::string dump() override;

private:
    graphics::Vector2d<float> _center;
    float _r;
};
} // namespace ample::geometry
