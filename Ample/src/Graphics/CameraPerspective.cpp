#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraPerspective.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
CameraPerspective::CameraPerspective(const Vector2d<pixel_t> &viewSize,
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
      _viewMatrixId(glGetUniformLocation(_programId, "view_matrix")),
      _projectionMatrixId(glGetUniformLocation(_programId, "projection_matrix")),
      _eyeVectorId(glGetUniformLocation(_programId, "eye_position"))
{
    DEBUG("Setup perspective camera") << _programId << ' ' << _projectionMatrixId << ' ' << _viewMatrixId << ' ' << _fov << ' ' << _aspectRatio << ' ' << std::endl;
    exception::OpenGLException::handle();
}

void CameraPerspective::look()
{
    _viewport.set();
    auto viewMatrix = glm::lookAt(glm::vec3{_position.x, _position.y, _position.z},
                                  glm::vec3{_target.x, _target.y, _target.z},
                                  glm::vec3{_angle.x, _angle.y, _angle.z});
    auto projectionMatrix = glm::perspective(glm::radians(_fov),
                                             _aspectRatio,
                                             _nearClip,
                                             _farClip);
    glm::vec3 eyePosition{_position.x, _position.y, _position.z};

    glUniformMatrix4fv(_projectionMatrixId, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(_viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniform3fv(_eyeVectorId, 1, glm::value_ptr(eyePosition));

    exception::OpenGLException::handle();
}

void CameraPerspective::unlook()
{
    // DEBUG("STUB for ortho camera unlook()");
}
} // namespace ample::graphics
