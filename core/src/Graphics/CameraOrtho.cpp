#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CameraOrtho.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
CameraOrtho::CameraOrtho(const Vector2d<pixel_t> &viewSize,
                         const Vector2d<pixel_t> &viewPosition,
                         const Vector3d<float> &eyePos,
                         const Vector3d<float> &direction,
                         float left,
                         float right,
                         float bottom,
                         float top)
    : Camera(viewSize, viewPosition, eyePos, direction),
      _left(left),
      _right(right),
      _bottom(bottom),
      _top(top),
      _programId(shaders::ShaderProcessor::instance().getProgramId()),
      _viewMatrixId(glGetUniformLocation(_programId, "view_matrix")),
      _projectionMatrixId(glGetUniformLocation(_programId, "projection_matrix")),
      _eyeVectorId(glGetUniformLocation(_programId, "eye_position"))
{
    DEBUG("Setup ortho camera");
    exception::OpenGLException::handle();
}

void CameraOrtho::look()
{
    _viewport.set();
    auto viewMatrix = glm::lookAt(_position, _position + _direction, {0, 1, 0});
    auto projectionMatrix = glm::ortho(_left, _right, _bottom, _top);
    glm::vec3 eyePosition{_position.x, _position.y, _position.z};

    glUniformMatrix4fv(_projectionMatrixId, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(_viewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniform3fv(_eyeVectorId, 1, glm::value_ptr(eyePosition));

    exception::OpenGLException::handle();
}

void CameraOrtho::unlook()
{
    // DEBUG("STUB for ortho camera unlook()");
}

void CameraOrtho::setLeft(float left) { _left = left; }
void CameraOrtho::setRight(float right) { _right = right; }
void CameraOrtho::setBottom(float bottom) { _bottom = bottom; }
void CameraOrtho::setTop(float top) { _top = top; }

float CameraOrtho::getLeft() const { return _left; }
float CameraOrtho::getRight() const { return _right; }
float CameraOrtho::getBottom() const { return _bottom; }
float CameraOrtho::getTop() const { return _top; }
} // namespace ample::graphics
