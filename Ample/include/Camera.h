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
        Viewport(Vector2d<pixel_t> size, Vector2d<pixel_t> pos = {0, 0});
        Viewport &operator=(const Viewport &) = default;
        Viewport(const Viewport &) = default;
        void set();
        Vector2d<pixel_t> size;
        Vector2d<pixel_t> position;
    };

public:
    Camera(Vector2d<pixel_t> viewSize,
           Vector2d<pixel_t> viewPosition,
           Vector3d<float> eyePos,
           Vector3d<float> targetPos,
           float ratio = 1.0);

    virtual void look() = 0;
    virtual void unlook() = 0;

    void setViewport(Vector2d<pixel_t> &&size, Vector2d<pixel_t> &&pos);
    void setViewport(const Vector2d<pixel_t> &size, const Vector2d<pixel_t> &pos);
    void setViewport(Vector2d<pixel_t> &&size);
    void setViewport(const Vector2d<pixel_t> &size);

    void setRatio(float ratio);
    float getRatio() const;

    void translateEye(Vector3d<float> &&);
    void translateEye(const Vector3d<float> &);

    void rotateHead(Vector3d<float> &&);
    void rotateHead(const Vector3d<float> &);

    void setEyeTranslated(Vector3d<float> &&);
    void setEyeTranslated(const Vector3d<float> &);
    void setHeadRotated(Vector3d<float> &&);
    void setHeadRotated(const Vector3d<float> &);

    float getEyeX() const;
    float getEyeY() const;
    float getEyeZ() const;

    float getHeadAngleX() const;
    float getHeadAngleY() const;
    float getHeadAngleZ() const;

    void setTarget(Vector3d<float> &&);
    void setTarget(const Vector3d<float> &);
    void translateTarget(Vector3d<float> &&);
    void translateTarget(const Vector3d<float> &);

    virtual ~Camera() = default;

protected:
    Viewport _viewport;
    Vector3d<float> _position{0.0, 0.0, 0.0};
    Vector3d<float> _target{0.0, 0.0, 0.0};
    Vector3d<float> _angle{0.0, 1.0, 0.0};
    float _ratio = 1.0;
};
} // namespace ample::graphics
