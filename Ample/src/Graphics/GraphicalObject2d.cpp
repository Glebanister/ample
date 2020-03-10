#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float depth,
                                     const float z)
    : _programId(shaders::ShaderProcessor::instance().getProgramId()),
      _modelMatrixId(glGetUniformLocation(_programId, "model_matrix")),
      _depth(depth),
      _z(z)
{
    DEBUG("Setup graphical object 2d");
    exception::OpenGLException::handle();
    std::vector<Vector3d<float>> sideArray(graphicalShape.size() * 2 + 2);
    std::vector<Vector3d<float>> faceArray(graphicalShape.size());
    for (size_t vId = 0; vId < graphicalShape.size(); ++vId)
    {
        sideArray[vId * 2] = {graphicalShape[vId].x,
                              graphicalShape[vId].y,
                              depth + z};
        sideArray[vId * 2 + 1] = {graphicalShape[vId].x,
                                  graphicalShape[vId].y,
                                  z};
        faceArray[vId] = {graphicalShape[vId].x,
                          graphicalShape[vId].y,
                          z};
    }
    sideArray[sideArray.size() - 2] = sideArray[0];
    sideArray[sideArray.size() - 1] = sideArray[1];
    _sideArray = std::make_unique<VertexArray>(std::move(sideArray), GL_TRIANGLE_STRIP);
    _faceArray = std::make_unique<VertexArray>(std::move(faceArray), GL_TRIANGLE_FAN);
}

void GraphicalObject2d::draw(glm::mat4 rotated,
                             glm::mat4 translated)
{
    rotated *= _rotated;
    translated *= _translated;
    glm::mat4 modelMatrix = translated * rotated;
    glUniformMatrix4fv(_modelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    exception::OpenGLException::handle();
    _sideArray->execute();
    _faceArray->execute();
    for (auto subObject : _subObjects)
    {
        subObject->draw(rotated, translated);
    }
    exception::OpenGLException::handle();
}

void GraphicalObject2d::setFaceColor256(Color color)
{
    _faceArray->setColor256(color.r, color.g, color.b);
}

void GraphicalObject2d::setSideColor256(Color color)
{
    _sideArray->setColor256(color.r, color.g, color.b);
}
} // namespace ample::graphics
