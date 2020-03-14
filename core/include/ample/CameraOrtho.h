#pragma once

#include "Camera.h"

namespace ample::graphics
{
class CameraOrtho : public Camera
{
public:
    CameraOrtho(const Vector2d<pixel_t> &viewSize,
                const Vector2d<pixel_t> &viewPosition,
                const Vector3d<float> &eyePos,
                const Vector3d<float> &direction,
                float left,
                float right,
                float bottom,
                float top);

    void look() override;
    void unlook() override;

    void setLeft(float);
    void setRight(float);
    void setBottom(float);
    void setTop(float);

    float getLeft() const;
    float getRight() const;
    float getBottom() const;
    float getTop() const;

private:
    float _left;
    float _right;
    float _bottom;
    float _top;
    GLuint _programId;
    GLuint _viewMatrixId;
    GLuint _projectionMatrixId;
    GLuint _eyeVectorId;
};
} // namespace ample::graphics
