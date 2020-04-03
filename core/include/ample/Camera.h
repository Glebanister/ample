#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "Vector2d.h"
#include "Vector3d.h"
#include "Behaviour.h"

namespace ample::graphics
{
using pixel_t = std::int32_t;
class Camera : public activity::Behavior
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
           Vector3d<float> targetPos);

    virtual void look() = 0;
    virtual void unlook() = 0;

    void setViewport(Vector2d<pixel_t> &&size, Vector2d<pixel_t> &&pos);
    void setViewport(const Vector2d<pixel_t> &size, const Vector2d<pixel_t> &pos);
    void setViewport(Vector2d<pixel_t> &&size);
    void setViewport(const Vector2d<pixel_t> &size);

    void translate(const glm::vec3 &);
    void moveForward(float);
    void moveRight(float);
    void moveUp(float);

    void rotate(const glm::vec3 &axis, const float angle);
    void rotateForward(float);
    void rotateRight(float);
    void rotateUp(float);

    float getX() const noexcept;
    float getY() const noexcept;
    float getZ() const noexcept;

    void setVisibility(const bool);

    virtual ~Camera() = default;

protected:
    Viewport _viewport;
    glm::vec3 _position{0.0f};
    glm::vec3 _direction{0.0, 0.0, 1.0};
    glm::vec3 _head{0.0, 1.0, 0.0};
    glm::vec3 _right{1.0, 0.0, 0.0};

    bool _visible = true;
};
} // namespace ample::graphics
