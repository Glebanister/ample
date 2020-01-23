#pragma once

#include "Vector.h"

namespace graphics
{
class WindowObject
{
public:
    virtual void draw() = 0;
};

class UpdatableObject
{
public:
    virtual void update() = 0;
};

class WindowObject2d : public WindowObject
{
public:
    WindowObject2d();

    WindowObject2d(const geometry::Vector2d &pos);

    void translate(const double &dx, const double &dy);

    void translate(const geometry::Vector2d &vector);

    void rotate(const double &rotAngle);

    void scale(const double &scaleCoef);

protected:
    geometry::Vector2d pos = {0, 0};
    double angle = 0.0;
    double scaleDegree = 1.0;
};
} // namespace graphics
