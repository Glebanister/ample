#pragma once

#include "Camera.h"

namespace ample::graphics
{
class CameraPerspective : public Camera
{
public:
    CameraPerspective(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView, double ratio = 1.0);
    CameraPerspective(pixel_t wView, pixel_t hView, double ratio = 1.0);

    void look() override;
    void unlook() override;

    double getLeft() const;
    double getRight() const;
    double getBottom() const;
    double getTop() const;
    double getNear() const;
    double getFar() const;

    void setPerspective(double left, double right, double bottom, double top, double near, double far);

protected:
    double raito = 1.0;
    double _left, _right, _bottom, _top, _near, _far;
};
} // namespace ample::graphics
