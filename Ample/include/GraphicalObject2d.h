#pragma once

#include <vector>

#include "GraphicalObject.h"
#include "Vector2d.h"

namespace ample::graphics
{
class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d() = default;
    GraphicalObject2d(const std::vector<Vector2d<double>> &);

    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual double getZ() const = 0;

    virtual double getAngleX() const = 0;
    virtual double getAngleY() const = 0;
    virtual double getAngleZ() const = 0;

    virtual double getScaleX() const = 0;
    virtual double getScaleY() const = 0;
    virtual double getScaleZ() const = 0;

    void draw() override;
    void setRatio(double);
    double getRatio() const;

protected:
    void drawSelf() override;
    std::vector<Vector2d<double>> _graphicalShape;
    double _ratio = 1.0;
};
} // namespace graphics
