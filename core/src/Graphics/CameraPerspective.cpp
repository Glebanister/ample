#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "CameraPerspective.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
CameraPerspective::CameraPerspective(const Vector2d<pixel_t> &viewSize,
                                     const Vector2d<pixel_t> &viewPosition,
                                     const Vector3d<float> &eyePos,
                                     const Vector3d<float> &direction,
                                     float fov,
                                     float aspectRatio,
                                     float nearClip,
                                     float farClip)
    : Camera(viewSize, viewPosition, eyePos, direction),
      _fov(fov),
      _aspectRatio(aspectRatio),
      _nearClip(nearClip),
      _farClip(farClip),
      _viewMatrixUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_viewMatrix, "view_matrix")),
      _projectionMatrixUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_projectionMatrix, "projection_matrix"))
{
    DEBUG("Setup perspective camera") << _fov << ' ' << _aspectRatio << ' ' << std::endl;
    exception::OpenGLException::handle();
}

void CameraPerspective::look()
{
    if (!_visible)
    {
        return;
    }
    _viewport.set();
    _viewMatrix = glm::lookAt(_position, _position + _direction, _head);
    _projectionMatrix = glm::perspective(glm::radians(_fov),
                                         _aspectRatio,
                                         _nearClip,
                                         _farClip);

    _viewMatrixUniform->load();
    _projectionMatrixUniform->load();

    exception::OpenGLException::handle();
}

void CameraPerspective::unlook()
{
    // DEBUG("STUB for ortho camera unlook()");
}

void CameraPerspective::setFov(float fov) { _fov = fov; }
void CameraPerspective::setNearClip(float nearClip) { _nearClip = nearClip; }
void CameraPerspective::setFarClip(float farClip) { _farClip = farClip; }
void CameraPerspective::setAspectRatio(float ratio) { _aspectRatio = ratio; }

float CameraPerspective::getFov() const { return _fov; }
float CameraPerspective::getNearClip() const { return _nearClip; }
float CameraPerspective::getFarClip() const { return _farClip; }
float CameraPerspective::getAspectRatio() const { return _aspectRatio; }
} // namespace ample::graphics
