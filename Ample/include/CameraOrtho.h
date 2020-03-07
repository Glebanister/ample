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
                const Vector3d<float> &targetPos,
                float coordRatio,
                float fov,
                float aspectRatio,
                float nearClip,
                float farClip);

    void look() override;
    void unlook() override;

private:
    float _fov;
    float _aspectRatio;
    float _nearClip;
    float _farClip;
    GLuint _programId;
    GLuint _viewMatrixId;
    GLuint _projectionMatrixId;
};
} // namespace ample::graphics
