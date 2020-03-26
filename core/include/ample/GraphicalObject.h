#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <GL/gl.h>

#include "Vector3d.h"
#include "ShaderProcessor.h"
#include "Behaviour.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Behaviour
{
public:
    GraphicalObject();

    void draw(glm::mat4 scaled = glm::mat4{1.0f},
              glm::mat4 rotated = glm::mat4{1.0f},
              glm::mat4 translated = glm::mat4{1.0f});
    virtual void drawSelf() = 0;
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

protected:
    std::vector<GraphicalObject *> _subObjects;
    glm::mat4 _translated{1.0f};
    glm::mat4 _scaled{1.0f};
    glm::mat4 _rotated{1.0f};
    glm::mat4 _modelMatrix{1.0f};
    std::unique_ptr<shaders::ShaderProcessor::Uniform> _modelMatrixUniform;
};
} // namespace ample::graphics
