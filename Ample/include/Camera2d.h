#pragma once

#include "Camera.h"

namespace ample::graphics
{
class Camera2d : public Camera
{
public:
    Camera2d(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView);
    Camera2d(pixel_t wView, pixel_t hView);

    void look() override;
    void unlook() override;

    virtual void scaleX(double) = 0;
    virtual void scaleY(double) = 0;
    virtual void scaleZ(double) = 0;

    virtual void translateX(pixel_t) = 0;
    virtual void translateY(pixel_t) = 0;
    virtual void translateZ(pixel_t) = 0;

    virtual void rotateX(double) = 0;
    virtual void rotateY(double) = 0;
    virtual void rotateZ(double) = 0;

    virtual double getScaleX() const = 0;
    virtual double getScaleY() const = 0;
    virtual double getScaleZ() const = 0;

    virtual pixel_t getX() const = 0;
    virtual pixel_t getY() const = 0;
    virtual pixel_t getZ() const = 0;

    virtual double getAngleX() const = 0;
    virtual double getAngleY() const = 0;
    virtual double getAngleZ() const = 0;

protected:
    virtual pixel_t getLeft() const = 0;
    virtual pixel_t getRight() const = 0;
    virtual pixel_t getBottom() const = 0;
    virtual pixel_t getTop() const = 0;
    virtual pixel_t getNear() const = 0;
    virtual pixel_t getFar() const = 0;
};
} // namespace ample::graphics
