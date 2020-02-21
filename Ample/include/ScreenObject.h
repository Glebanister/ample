#pragma once

#include <vector>

#include "GraphicalObject2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
class ScreenObject : public GraphicalObject2d
{
public:
    ScreenObject(const std::vector<Vector2d<pixel_t>> &, Vector3d<pixel_t> position);
    ScreenObject(const std::vector<Vector2d<pixel_t>> &);

    pixel_t getX() const override;
    pixel_t getY() const override;
    pixel_t getZ() const override;

    radians_t getAngleX() const override;
    radians_t getAngleY() const override;
    radians_t getAngleZ() const override;

    double getScaleX() const override;
    double getScaleY() const override;
    double getScaleZ() const override;

    void rotateX(radians_t angle);
    void rotateY(radians_t angle);
    void rotateZ(radians_t angle);

    void translateX(pixel_t dx);
    void translateY(pixel_t dy);
    void translateZ(pixel_t dz);

    void scaleX(double coef);
    void scaleY(double coef);
    void scaleZ(double coef);

protected:
    Vector3d<pixel_t> _position{0.0, 0.0, 0.0};
    Vector3d<pixel_t> _scale{1.0, 1.0, 1.0};
    Vector3d<pixel_t> _angle{0.0, 0.0, 0.0};
};
} // namespace ample::graphics
