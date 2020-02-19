#pragma once

#include "Camera2d.h"
#include "Vector2d.h"

namespace ample::graphics
{
typedef double pixel_t;

class ScreenCamera : public Camera2d
{
public:
    ScreenCamera(Vector2d position, pixel_t width, pixel_t height);

    ScreenCamera(pixel_t width, pixel_t height);

    void look() override;
    void unlook() override;
    void scaleX(double) override;
    void scaleY(double) override;
    void translateX(pixel_t) override;
    void translateY(pixel_t) override;
    void rotateZ(double) override;

    double getScaleX() const override;
    double getScaleY() const override;
    pixel_t getX() const override;
    pixel_t getY() const override;
    double getAngleZ() const override;

private:
    Vector2d _position;
    double _angle = 0.0;
    double _scaleX = 1.0, _scaleY = 1.0;
    pixel_t _width, _height;
};
} // namespace ample::graphics
