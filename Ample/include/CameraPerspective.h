#pragma once

#include "Camera.h"

namespace ample::graphics
{
class CameraPerspective : public Camera
{
public:
    CameraPerspective(const Vector2d<pixel_t> &viewSize,
                      const Vector2d<pixel_t> &viewPosition,
                      const Vector3d<float> &eyePos,
                      const Vector3d<float> &direction,
                      float fov,
                      float aspectRatio,
                      float nearClip,
                      float farClip);

    void look() override;
    void unlook() override;

    void setFov(float);
    void setNearClip(float);
    void setFarClip(float);

    float getFov() const;
    float getNearClip() const;
    float getFarClip() const;

private:
    float _fov;
    float _aspectRatio;
    float _nearClip;
    float _farClip;
    GLuint _programId;
    GLuint _viewMatrixId;
    GLuint _projectionMatrixId;
    GLuint _eyeVectorId;
};
} // namespace ample::graphics
