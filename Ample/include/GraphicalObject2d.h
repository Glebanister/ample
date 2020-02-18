#pragma once

#include <vector>

#include "GraphicalObject.h"

namespace graphics
{
typedef double pixel_t;

struct Vector2d
{
    Vector2d(pixel_t xp, pixel_t yp)
        : x(xp), y(yp) {}
    Vector2d()
        : Vector2d(0.0, 0.0) {}

    pixel_t x, y;
};

class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const std::vector<Vector2d> &);

    virtual pixel_t getX() = 0;
    virtual pixel_t getY() = 0;
    virtual double getAngle() = 0;
    virtual double getScaleX() = 0;
    virtual double getScaleY() = 0;

    void draw() override;

private:
    void drawSelf() override;
    std::vector<Vector2d> _graphicalShape;
};
} // namespace graphics
