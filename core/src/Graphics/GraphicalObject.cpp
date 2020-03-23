#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicalObject.h"
#include "ShaderProcessor.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::graphics
{
GraphicalObject::GraphicalObject()
    : _modelMatrixUniform(std::make_unique<shaders::ShaderProcessor::Uniform>(_modelMatrix, "model_matrix")) {}

void GraphicalObject::addSubObject(GraphicalObject &object)
{
    activity::Behaviour::addBehaviour(object);
    _subObjects.push_back(&object);
}

float GraphicalObject::getX() const { return _translated[0][0]; }
float GraphicalObject::getY() const { return _translated[1][1]; }
float GraphicalObject::getZ() const { return _translated[2][2]; }

void GraphicalObject::setTranslate(glm::vec3 vector)
{
    _translated = glm::translate(vector);
}
void GraphicalObject::translate(glm::vec3 vector)
{
    _translated *= glm::translate(vector);
}

void GraphicalObject::setRotate(glm::vec3 axis, float angle)
{
    _rotated = glm::rotate(glm::radians(angle), axis);
}
void GraphicalObject::rotate(glm::vec3 axis, float angle)
{
    _rotated = glm::rotate(_rotated, glm::radians(angle), axis);
}

void GraphicalObject::draw(glm::mat4 rotated,
                           glm::mat4 translated)
{
    DEBUG("start drawing Graphical object");
    rotated *= _rotated;
    translated *= _translated;
    _modelMatrix = translated * rotated;
    DEBUG("loading uniform");
    _modelMatrixUniform->load();
    exception::OpenGLException::handle();
    DEBUG("loading uniform done");
    DEBUG("drawing self");
    drawSelf();
    exception::OpenGLException::handle();
    DEBUG("drawing self done");
    for (auto subObject : _subObjects)
    {
        subObject->draw(rotated, translated);
    }
    DEBUG("checking for error");
    exception::OpenGLException::handle();
    DEBUG("Graphical object is done");
}
} // namespace ample::graphics
