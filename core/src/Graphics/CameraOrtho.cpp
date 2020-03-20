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
                         float top,
                         float near,
                         float far)
    : Camera(viewSize, viewPosition, eyePos, direction),
      _left(left),
      _right(right),
      _bottom(bottom),
      _top(top),
      _near(near),
      _far(far),
      _viewMatrixUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_viewMatrix, "view_matrix")),
      _projectionMatrixUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_projectionMatrix, "projection_matrix"))
{
    DEBUG("Setup ortho camera");
    exception::OpenGLException::handle();
}

void CameraOrtho::look()
{
    _viewport.set();
    _viewMatrix = glm::lookAt(_position, _position + _direction, {0, 1, 0});
    _projectionMatrix = glm::ortho(_left, _right, _bottom, _top, _near, _far);
    _viewMatrixUniform->load();
    _projectionMatrixUniform->load();

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
void CameraOrtho::setNear(float near) { _near = near; }
void CameraOrtho::setFar(float far) { _far = far; }

float CameraOrtho::getLeft() const { return _left; }
float CameraOrtho::getRight() const { return _right; }
float CameraOrtho::getBottom() const { return _bottom; }
float CameraOrtho::getTop() const { return _top; }
float CameraOrtho::getNear() const { return _near; }
float CameraOrtho::getFar() const { return _far; }
} // namespace ample::graphics
