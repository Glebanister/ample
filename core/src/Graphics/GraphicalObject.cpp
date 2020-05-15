#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>

#include "Debug.h"
#include "Exception.h"
#include "GraphicalObject.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
GraphicalObject::GraphicalObject(const std::string &name,
                                 const std::string &className,
                                 const glm::mat4 &translated,
                                 const glm::mat4 &scaled,
                                 const glm::mat4 &rotated)
    : NamedStoredObject(name, className),
      _translated(translated),
      _scaled(scaled),
      _rotated(rotated),
      _modelMatrixUniform(_modelMatrix, "model_matrix")
{
    _position = translated * rotated * scaled * glm::vec4{_position, 1};
}

void GraphicalObject::addSubObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::addBehavior(std::static_pointer_cast<Behavior>(object));
    _subObjects.push_back(object);
}

void GraphicalObject::removeSubObject(std::shared_ptr<GraphicalObject> object)
{
    activity::Behavior::removeBehavior(std::static_pointer_cast<Behavior>(object));
    std::remove(_subObjects.begin(), _subObjects.end(), object);
}

float GraphicalObject::getX() const { return _position[0]; }
float GraphicalObject::getY() const { return _position[1]; }
float GraphicalObject::getZ() const { return _position[2]; }
float GraphicalObject::getAxisAngle() const noexcept { return _angle; }

void GraphicalObject::setTranslate(const glm::vec3 &vector) noexcept
{
    _translated = glm::translate(vector);
    _position = vector;
}
void GraphicalObject::translate(const glm::vec3 &vector) noexcept
{
    _translated *= glm::translate(vector);
    _position += vector;
}

void GraphicalObject::setRotate(const glm::vec3 &axis, const float angle) noexcept
{
    _rotated = glm::rotate(glm::radians(angle), axis);
    _angle = glm::radians(angle); // TODO: not expected result
}
void GraphicalObject::rotate(const glm::vec3 &axis, const float angle) noexcept
{
    _rotated = glm::rotate(_rotated, glm::radians(angle), axis);
    _angle += glm::radians(angle);
}

void GraphicalObject::setScale(const glm::vec3 &coef) noexcept
{
    _scaled = glm::scale(coef);
}

void GraphicalObject::scale(const glm::vec3 &coef) noexcept
{
    _scaled *= glm::scale(coef);
}

void GraphicalObject::bindTexture(std::shared_ptr<Texture> texturePtr) noexcept
{
    _texturePtr = texturePtr;
}

void GraphicalObject::bindVertexArray(std::shared_ptr<VertexArray> ptr) noexcept
{
    _vertexArrayPtr = ptr;
}

void GraphicalObject::drawSelf() {}

void GraphicalObject::draw(glm::mat4 scaled,
                           glm::mat4 rotated,
                           glm::mat4 translated)
{
    rotated *= _rotated;
    translated *= _translated;
    scaled *= _scaled;
    _modelMatrix = translated * rotated * scaled;
    _modelMatrixUniform.load();
    if (_texturePtr)
    {
        _texturePtr->pin();
    }
    if (_vertexArrayPtr)
    {
        _vertexArrayPtr->execute();
    }
    drawSelf();
    if (_texturePtr)
    {
        _texturePtr->unpin();
    }
    for (auto subObject : _subObjects)
    {
        subObject->draw(scaled, rotated, translated);
    }
    exception::OpenGLException::handle();
}

GraphicalObject::GraphicalObject(filing::JsonIO input)
    : GraphicalObject(input.read<std::string>("name"),
                      input.read<std::string>("class_name"),
                      input.read<glm::mat4>("translated"),
                      input.read<glm::mat4>("scaled"),
                      input.read<glm::mat4>("rotated"))
{
    _texutureName = input.read<std::string>("texture_name");
}

std::string GraphicalObject::getTextureName() const noexcept
{
    if (_texturePtr)
    {
        return _texturePtr->name();
    }
    return _texutureName;
}

std::string GraphicalObject::dump()
{
    filing::JsonIO output = NamedStoredObject::dump();
    output.write<glm::mat4>("translated", _translated);
    output.write<glm::mat4>("scaled", _scaled);
    output.write<glm::mat4>("rotated", _rotated);
    output.write<std::string>("texture_name", _texturePtr ? _texturePtr->name() : "");

    return output;
}

std::shared_ptr<Texture> GraphicalObject::texture() const noexcept
{
    return _texturePtr;
}
} // namespace ample::graphics
