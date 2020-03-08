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

void LightSource::onActive()
{
    GraphicalObject::onActive();
    glEnable(GLenum(_index));
    glLightfv(_index, GL_AMBIENT, glm::value_ptr(_ambient));
    glLightfv(_index, GL_DIFFUSE, glm::value_ptr(_diffuse));
    glLightfv(_index, GL_SPECULAR, glm::value_ptr(_specular));
    exception::OpenGLException::handle();
}
} // namespace ample::graphics::light
