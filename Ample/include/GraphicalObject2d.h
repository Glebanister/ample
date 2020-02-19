#pragma once

#include <vector>

#include "GraphicalObject.h"
#include "Vector2d.h"

namespace ample::graphics
{
typedef double pixel_t;

class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const std::vector<Vector2d> &);

    virtual pixel_t getX() const = 0;
    virtual pixel_t getY() const = 0;
    virtual double getAngle() const = 0;
    virtual double getScaleX() const = 0;
    virtual double getScaleY() const = 0;

    void draw() override;

private:
    void drawSelf() override;
    std::vector<Vector2d> _graphicalShape;
};
} // namespace graphics
