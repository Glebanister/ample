#pragma once

#include <vector>

#include "GraphicalObject2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
using pixel_t = std::int32_t;
using radian_t = double;

class ScreenObject : public GraphicalObject2d
{
public:
    ScreenObject(const std::vector<Vector2d<pixel_t>> &, Vector3d<pixel_t> position);
    ScreenObject(const std::vector<Vector2d<pixel_t>> &, Vector2d<pixel_t> position);
    ScreenObject(const std::vector<Vector2d<pixel_t>> &);

    double getX() const override;
    double getY() const override;
    double getZ() const override;

    double getAngleX() const override;
    double getAngleY() const override;
    double getAngleZ() const override;

    double getScaleX() const override;
    double getScaleY() const override;
    double getScaleZ() const override;

    void rotate(radian_t x, radian_t y, radian_t z);
    void translate(pixel_t x, pixel_t y, pixel_t z);
    void scale(double x, double y, double z);

    void setPosition(pixel_t x, pixel_t y, pixel_t z);
    void setAngle(radian_t x, radian_t y, radian_t z);
    void setScale(double x, double y, double z);

protected:
    Vector3d<pixel_t> _position{0, 0, 0};
    Vector3d<double> _scale{1.0, 1.0, 1.0};
    Vector3d<radian_t> _angle{0.0, 0.0, 0.0};
};
} // namespace ample::graphics
