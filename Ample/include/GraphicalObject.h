#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Vector3d.h"
#include "Behaviour.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Behaviour
{
public:
    virtual void draw(glm::mat4 rotated = glm::mat4{1.0f},
                      glm::mat4 translated = glm::mat4{1.0f}) = 0;
    void addSubObject(GraphicalObject &object);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setTranslate(glm::vec3 vector);
    void translate(glm::vec3 vector);

    void setRotate(glm::vec3 axis, float angle);
    void rotate(glm::vec3 axis, float angle);

protected:
    std::vector<GraphicalObject *> _subObjects;
    glm::mat4 _translated{1.0f};
    glm::mat4 _rotated{1.0f};
};
} // namespace ample::graphics
