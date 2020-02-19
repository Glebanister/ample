#pragma once

#include "Camera2d.h"
#include "Vector2d.h"

namespace ample::graphics
{
typedef double pixel_t;

class ScreenCamera : public Camera2d
{
public:
    ScreenCamera(Vector2d camPos, Vector2d camSizes,
                 Vector2d viewportPos, Vector2d viewportSizes);

    ScreenCamera(Vector2d camSizes, Vector2d viewportSizes);
    ScreenCamera(Vector2d viewportSizes);

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
    double _angle = 0.0;
    double _scaleX = 1.0, _scaleY = 1.0;
    Vector2d _camSizes;
    Vector2d _camPos{0.0, 0.0};
};
} // namespace ample::graphics
