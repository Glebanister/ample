#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "CameraOrtho.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
CameraOrtho::CameraOrtho(const Vector2d<pixel_t> &viewSize,
                                     const Vector2d<pixel_t> &viewPosition,
                                     const Vector3d<float> &eyePos,
                                     const Vector3d<float> &targetPos,
                                     float coordRatio,
                                     float fov,
                                     float aspectRatio,
                                     float nearClip,
                                     float farClip)
    : Camera(viewSize, viewPosition, eyePos, targetPos, coordRatio),
      _fov(fov),
      _aspectRatio(aspectRatio),
      _nearClip(nearClip),
      _farClip(farClip),
      _programId(shaders::ShaderProcessor::instance().getProgramId()),
      _viewMatrixId(glGetUniformLocation(_programId, "ViewMatrix")),
      _projectionMatrixId(glGetUniformLocation(_programId, "ProjectionMatrix"))
{
    DEBUG("Setup perspective camera");
    exception::OpenGLException::handle();
}

void CameraOrtho::look()
{
    _viewport.set();
    auto viewMatrix = glm::lookAt(glm::vec3{_position.x, _position.y, _position.z},
                                  glm::vec3{_target.x, _target.y, _target.z},
                                  glm::vec3{_angle.x, _angle.y, _angle.z});
    auto projectionMatrix = glm::perspective(glm::radians(_fov),
                                             _aspectRatio,
                                             _nearClip,
                                             _farClip);
    glUniformMatrix4fv(_viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(_projectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);
    exception::OpenGLException::handle();
}

void CameraOrtho::unlook()
{
    // DEBUG("STUB for ortho camera unlook()");
}
} // namespace ample::graphics
