#pragma once

#include <memory>

#include "Camera.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
class CameraPerspective : public Camera
{
public:
    CameraPerspective(const std::string &name,
                      const Vector2d<pixel_t> &viewSize,
                      const Vector2d<pixel_t> &viewPosition,
                      const Vector3d<float> &eyePos,
                      const Vector3d<float> &direction,
                      float fov,
                      float aspectRatio,
                      float nearClip,
                      float farClip);

    CameraPerspective(const filing::JsonIO &input);
    std::string dump() override;

    void look() override;
    void unlook() override;

    void setFov(float);
    void setNearClip(float);
    void setFarClip(float);
    void setAspectRatio(float);

    float getFov() const;
    float getNearClip() const;
    float getFarClip() const;
    float getAspectRatio() const;

private:
    float _fov;
    float _aspectRatio;
    float _nearClip;
    float _farClip;
    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};

    std::unique_ptr<shaders::ShaderProcessor::Uniform> _viewMatrixUniform;
    std::unique_ptr<shaders::ShaderProcessor::Uniform> _projectionMatrixUniform;
    std::unique_ptr<shaders::ShaderProcessor::Uniform> _eyeVectorUniform;
};
} // namespace ample::graphics
