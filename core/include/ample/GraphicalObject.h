#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <GL/gl.h>

#include "Vector3d.h"
#include "ShaderProcessor.h"
#include "Behaviour.h"
#include "Texture.h"
#include "VertexArray.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Behaviour
{
public:
    GraphicalObject(const glm::mat4 &translated = glm::mat4{1.0f},
                    const glm::mat4 &scaled = glm::mat4{1.0f},
                    const glm::mat4 &rotated = glm::mat4{1.0f});

    void draw(glm::mat4 scaled = glm::mat4{1.0f},
              glm::mat4 rotated = glm::mat4{1.0f},
              glm::mat4 translated = glm::mat4{1.0f});
    virtual void drawSelf();
    void addSubObject(GraphicalObject &object);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setScale(const glm::vec3 &) noexcept;
    void scale(const glm::vec3 &) noexcept;

    void setRotate(const glm::vec3 &axis, const float angle) noexcept;
    void rotate(const glm::vec3 &axis, const float angle) noexcept;

    void setTranslate(const glm::vec3 &) noexcept;
    void translate(const glm::vec3 &) noexcept;

    void bindTexture(std::shared_ptr<Texture> texturePtr) noexcept;

    void bindVertexArray(std::shared_ptr<VertexArray>) noexcept;

protected:
    glm::mat4 _modelMatrix{1.0f};

private:
    std::vector<GraphicalObject *> _subObjects;
    glm::mat4 _translated{1.0f};
    glm::mat4 _scaled{1.0f};
    glm::mat4 _rotated{1.0f};
    shaders::ShaderProcessor::Uniform _modelMatrixUniform;
    std::shared_ptr<Texture> _texturePtr = nullptr;
    std::shared_ptr<VertexArray> _vertexArrayPtr = nullptr;
};
} // namespace ample::graphics
