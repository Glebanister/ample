#pragma once

#include <vector>

#include "GraphicalObject2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
using pixel_t = std::int32_t;
using radian_t = float;

class ScreenObject : public GraphicalObject2d
{
public:
    ScreenObject(const std::vector<Vector2d<float>> &shape,
                 Vector3d<float> position,
                 const float depth);

    float getX() const override;
    float getY() const override;
    float getZ() const override;

    float getAngleX() const override;
    float getAngleY() const override;
    float getAngleZ() const override;

    float getScaleX() const override;
    float getScaleY() const override;
    float getScaleZ() const override;

    void rotate(Vector3d<float> angle);
    void translate(Vector2d<float> vector);
    void scale(Vector2d<float> scale);

    void setRotate(Vector3d<float> angle);
    void setTranslate(Vector2d<float> vector);
    void setScale(Vector2d<float> scale);

protected:
    Vector2d<float> _position{0.0, 0.0};
    Vector2d<float> _scale{1.0, 1.0};
    Vector3d<radian_t> _angle{0.0, 0.0, 0.0};
};
} // namespace ample::graphics
