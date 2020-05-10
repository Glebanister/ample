#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Behaviour.h"
#include "JsonIO.h"
#include "ShaderProcessor.h"
#include "Texture.h"
#include "Vector3d.h"
#include "VertexArray.h"

namespace ample::graphics
{
class GraphicalObject : public filing::NamedStoredObject, public activity::Behavior
{
public:
    GraphicalObject(const std::string &name,
                    const std::string &className,
                    const glm::mat4 &translated = glm::mat4{1.0f},
                    const glm::mat4 &scaled = glm::mat4{1.0f},
                    const glm::mat4 &rotated = glm::mat4{1.0f});

    explicit GraphicalObject(filing::JsonIO input);
    std::string dump() override;

    void draw(glm::mat4 scaled = glm::mat4{1.0f},
              glm::mat4 rotated = glm::mat4{1.0f},
              glm::mat4 translated = glm::mat4{1.0f});
    virtual void drawSelf();
    void addSubObject(std::shared_ptr<GraphicalObject> object);
    void removeSubObject(std::shared_ptr<GraphicalObject> object);

    float getX() const;
    float getY() const;
    float getZ() const;

    float getAxisAngle() const noexcept;

    void setScale(const glm::vec3 &) noexcept;
    void scale(const glm::vec3 &) noexcept;

    void setRotate(const glm::vec3 &axis, const float angle) noexcept;
    void rotate(const glm::vec3 &axis, const float angle) noexcept;

    void setTranslate(const glm::vec3 &) noexcept;
    void translate(const glm::vec3 &) noexcept;

    void bindTexture(std::shared_ptr<Texture> texturePtr) noexcept;
    std::shared_ptr<Texture> texture() const noexcept;
    std::string getTextureName() const noexcept;

    void bindVertexArray(std::shared_ptr<VertexArray>) noexcept;

protected:
    glm::mat4 _modelMatrix{1.0f};

private:
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
    glm::mat4 _translated{1.0f};
    glm::mat4 _scaled{1.0f};
    glm::mat4 _rotated{1.0f};
    shaders::ShaderProcessor::Uniform _modelMatrixUniform;
    std::shared_ptr<Texture> _texturePtr = nullptr;
    std::shared_ptr<VertexArray> _vertexArrayPtr = nullptr;
    std::string _texutureName;
    glm::vec3 _position = {0.0f, 0.0f, 0.0f};
    float _angle = 0.0f;
};
} // namespace ample::graphics
