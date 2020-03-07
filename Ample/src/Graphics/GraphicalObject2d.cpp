#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape)
    : _vertexArray(std::make_unique<VertexArray>(graphicalShape)),
      _programId(shaders::ShaderProcessor::instance().getProgramId()),
      _modelMatrixId(glGetUniformLocation(_programId, "ModelMatrix"))
{
    DEBUG("Setup graphical object 2d");
    exception::OpenGLException::handle();
}

void GraphicalObject2d::draw(Vector3d<float> &&scaled,
                             Vector3d<float> &&rotated,
                             Vector3d<float> &&translated)
{
    scaled *= Vector3d<float>{getScaleX(), getScaleY(), getScaleZ()};
    rotated += Vector3d<float>{getAngleX(), getAngleY(), getAngleZ()};
    translated += Vector3d<float>{getX(), getY(), getZ()};
    glm::mat4 modelMatrix = glm::scale(glm::mat4{1.0f}, glm::vec3{
                                                            scaled.x,
                                                            scaled.y,
                                                            scaled.z,
                                                        });
    modelMatrix = glm::rotate(modelMatrix, glm::radians(getAngleX()), glm::vec3{1.0, 0.0, 0.0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(getAngleY()), glm::vec3{0.0, 1.0, 0.0});
    modelMatrix = glm::rotate(modelMatrix, glm::radians(getAngleZ()), glm::vec3{0.0, 0.0, 1.0});
    modelMatrix = glm::translate(modelMatrix,
                                 glm::vec3{getX() * _ratio,
                                           getY() * _ratio,
                                           getZ() * _ratio});

    glUniformMatrix4fv(_modelMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
    exception::OpenGLException::handle();
    _vertexArray->execute();

    for (auto subObject : _subObjects)
    {
        subObject->draw(std::move(scaled), std::move(rotated), std::move(translated));
    }
}

void GraphicalObject2d::setRatio(float ratio)
{
    _ratio = ratio;
}

float GraphicalObject2d::getRatio() const
{
    return _ratio;
}

void GraphicalObject2d::setColor256(float r, float g, float b)
{
    _vertexArray->setColor256(r, g, b);
}
} // namespace ample::graphics
