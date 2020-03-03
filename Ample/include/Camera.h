#pragma once

#include <cstdint>

#include "Vector2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
using pixel_t = std::int32_t;
class Camera
{
protected:
    struct Viewport final
    {
        Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv);
        Viewport(pixel_t wv, pixel_t hv);
        Viewport &operator=(const Viewport &) = default;
        Viewport(const Viewport &) = default;

        void set();

        Vector2d<pixel_t> size;
        Vector2d<pixel_t> position;
    };

public:
    Camera(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
           Vector2d<double> cameraSize, Vector3d<double> cameraPosition,
           double ratio = 1.0);
    Camera(Vector2d<pixel_t> viewSize, Vector2d<pixel_t> viewPosition,
           Vector2d<double> cameraSize, Vector2d<double> cameraPosition,
           double ratio = 1.0);
    Camera(Vector2d<pixel_t> viewSize,
           Vector2d<double> cameraSize,
           double ratio = 1.0);
    Camera(Vector2d<pixel_t> cameraSize, double ratio = 1.0);

    virtual void look();
    virtual void unlook();

    void setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h);
    void setViewport(pixel_t w, pixel_t h);

    void setRatio(double ratio);

    void scale(double x, double y, double z);
    void translate(double x, double y, double z);
    void rotate(double x, double y, double z);

    void scaleSet(double x, double y, double z);
    void translateSet(double x, double y, double z);
    void rotateSet(double x, double y, double z);

    double getScaleX() const;
    double getScaleY() const;
    double getScaleZ() const;

    double getX() const;
    double getY() const;
    double getZ() const;

    double getAngleX() const;
    double getAngleY() const;
    double getAngleZ() const;

    pixel_t getViewportX() const;
    pixel_t getViewportY() const;
    pixel_t getViewportW() const;
    pixel_t getViewportH() const;

    double getWidth() const;
    double getHeight() const;

    double getLeft() const;
    double getRight() const;
    double getBottom() const;
    double getTop() const;
    double getNear() const;
    double getFar() const;

    void setPerspective(double left, double right, double bottom, double top, double near, double far);

protected:
    Viewport _viewport;
    Vector2d<double> _size;
    Vector3d<double> _position{0.0, 0.0, 0.0};
    Vector3d<double> _scale{1.0, 1.0, 1.0};
    Vector3d<double> _angle{0.0, 0.0, 0.0};
    double _ratio = 1.0;
    double _left, _right, _bottom, _top, _near, _far;
};
} // namespace ample::graphics
