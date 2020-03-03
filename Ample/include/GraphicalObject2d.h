#pragma once

#include <vector>
#include <GL/gl.h>
#include <iostream>

#include "GraphicalObject.h"
#include "Vector2d.h"
#include "VertexArray.h"

namespace ample::graphics
{
class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d() = delete;
    template <typename T>
    GraphicalObject2d(const std::vector<Vector2d<T>> &graphicalShape)
        : _vertexArray(std::make_shared<VertexArray>(graphicalShape)) {}

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

    void setColor256(double r, double g, double b);

protected:
    void drawSelf() override;
    double _ratio = 1.0;
    std::shared_ptr<VertexArray> _vertexArray;
};
} // namespace ample::graphics
