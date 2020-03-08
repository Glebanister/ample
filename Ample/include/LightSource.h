#pragma once

#include <glm/glm.hpp>

#include "Color.h"
#include "GraphicalObject.h"

namespace ample::graphics::light
{
class LightSource : public GraphicalObject
{
public:
    LightSource(const Color ambient,
                const Color diffuse,
                const Color specular);
    LightSource();

    glm::vec4 getAmbient() const;
    glm::vec4 getDiffuse() const;
    glm::vec4 getSpecular() const;
    void setAmbient(const glm::vec4 &color);
    void setDiffuse(const glm::vec4 &color);
    void setSpecular(const glm::vec4 &color);

    void draw() override;

private:
    float _intensity;
    glm::vec4 _ambient;
    glm::vec4 _diffuse;
    glm::vec4 _specular;
    uint8_t _index;

protected:
    void setupImpl() const;
    uint8_t getIndex() const;
};
} // namespace ample::graphics::light
