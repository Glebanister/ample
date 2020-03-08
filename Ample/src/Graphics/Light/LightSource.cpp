#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "LightSource.h"
#include "Exception.h"

namespace ample::graphics::light
{
LightSource::LightSource(const Color ambient,
                         const Color diffuse,
                         const Color specular)
    : _ambient(ambient.r, ambient.g, ambient.b, ambient.a),
      _diffuse(diffuse.r, diffuse.g, diffuse.b, diffuse.a),
      _specular(specular.r, specular.g, specular.b, specular.a)
{
    static uint8_t globalColorIndex = 0;
    _index = globalColorIndex++;
}

LightSource::LightSource()
    : LightSource(Color{}, Color{}, Color{}) {}

void LightSource::draw(Vector3d<float> &&scaled,
                       Vector3d<float> &&rotated,
                       Vector3d<float> &&translated)
{
    GraphicalObject::onActive();
    glEnable(GLenum(_index));
    glLightfv(_index, GL_AMBIENT, glm::value_ptr(_ambient));
    glLightfv(_index, GL_DIFFUSE, glm::value_ptr(_diffuse));
    glLightfv(_index, GL_SPECULAR, glm::value_ptr(_specular));
    glLightfv(_index, GL_POSITION, glm::value_ptr(_position));
    exception::OpenGLException::handle();
}

float LightSource::getX() const
{
    return _position[0];
}

float LightSource::getY() const
{
    return _position[1];
}

float LightSource::getZ() const
{
    return _position[2];
}

float LightSource::getAngleX() const
{
    return 0.0;
}

float LightSource::getAngleY() const
{
    return 0.0;
}

float LightSource::getAngleZ() const
{
    return 0.0;
}

float LightSource::getScaleX() const
{
    return 1.0;
}

float LightSource::getScaleY() const
{
    return 1.0;
}

float LightSource::getScaleZ() const
{
    return 1.0;
}
} // namespace ample::graphics::light
