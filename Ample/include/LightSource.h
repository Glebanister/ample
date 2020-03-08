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

    void draw(Vector3d<float> &&scaled = {1.0, 1.0, 1.0},
              Vector3d<float> &&rotated = {0.0, 0.0, 0.0},
              Vector3d<float> &&translated = {0.0, 0.0, 0.0}) override;

    float getX() const override;
    float getY() const override;
    float getZ() const override;

    float getAngleX() const override;
    float getAngleY() const override;
    float getAngleZ() const override;

    float getScaleX() const override;
    float getScaleY() const override;
    float getScaleZ() const override;

private:
    float _intensity;
    glm::vec4 _ambient;
    glm::vec4 _diffuse;
    glm::vec4 _specular;
    uint8_t _index;
    glm::vec4 _position;

protected:
    void setupImpl() const;
    uint8_t getIndex() const;
};
} // namespace ample::graphics::light
