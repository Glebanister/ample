#pragma once

#include "Camera2d.h"
#include "Vector2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
using pixel_t = double;
using radians_t = double;

class ScreenCamera : public Camera2d
{
public:
    ScreenCamera(Vector3d<pixel_t> cameraPosition, Vector2d<pixel_t> cameraSize,
                 Vector2d<pixel_t> viewportPosition, Vector2d<pixel_t> viewportSize);

    ScreenCamera(Vector2d<pixel_t> cameraPosition, Vector2d<pixel_t> cameraSize,
                 Vector2d<pixel_t> viewportPosition, Vector2d<pixel_t> viewportSize);

    ScreenCamera(Vector2d<pixel_t> cameraSize, Vector2d<pixel_t> viewportSize);
    ScreenCamera(Vector2d<pixel_t> viewportSize);

    void scaleX(double) override;
    void scaleY(double) override;
    void scaleZ(double) override;

    void translateX(pixel_t) override;
    void translateY(pixel_t) override;
    void translateZ(pixel_t) override;

    void rotateX(radians_t) override;
    void rotateY(radians_t) override;
    void rotateZ(radians_t) override;

    double getScaleX() const override;
    double getScaleY() const override;
    double getScaleZ() const override;

    pixel_t getX() const override;
    pixel_t getY() const override;
    pixel_t getZ() const override;

    radians_t getAngleX() const override;
    radians_t getAngleY() const override;
    radians_t getAngleZ() const override;

    void setCameraProperties(pixel_t left, pixel_t right,
                             pixel_t bottom, pixel_t top,
                             pixel_t near, pixel_t far);

    pixel_t getLeft() const override;
    pixel_t getRight() const override;
    pixel_t getBottom() const override;
    pixel_t getTop() const override;
    pixel_t getNear() const override;
    pixel_t getFar() const override;

private:
    Vector2d<pixel_t> _size;
    Vector3d<pixel_t> _position{0.0, 0.0, 0.0};
    Vector3d<double> _scale{1.0, 1.0, 1.0};
    Vector3d<radians_t> _angle{0.0, 0.0, 0.0};
    pixel_t _camLeft, _camRight, _camBot, _camTop, _camNear, _camFar;
};
} // namespace ample::graphics
