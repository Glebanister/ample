#include <GL/glu.h>

#include "Texture.h"
#include "Exception.h"
#include "Debug.h"
#include "ILEnvironment.h"
#include "OpenGLEnvironment.h"

namespace ample::graphics
{
TextureRaw::TextureRaw(const std::string &texturePath,
                       const graphics::Vector2d<int> &size,
                       const graphics::Vector2d<int> &position,
                       const channelMode mode)
    : texturePath(texturePath),
      size(size),
      position(position),
      mode(mode)
{
}

TextureRaw::TextureRaw(const Texture &other)
    : TextureRaw(other._raw) {}

Texture::PixelMap::PixelMap(const graphics::Vector2d<int> &size,
                            const channelMode mode)
    : _data(size.y * size.x * (mode == channelMode::RGB ? 3 : 4)),
      _size(size)
{
}

uint8_t *Texture::PixelMap::data()
{
    return _data.data();
}

int Texture::PixelMap::getWidth() const noexcept
{
    return _size.x;
}

int Texture::PixelMap::getHeight() const noexcept
{
    return _size.y;
}

Texture::Texture(const TextureRaw &rawTexture)
    : _raw(rawTexture)
{
    DEBUG("Loading texture " + _raw.texturePath);
    os::environment::ILEnvironment::instance();

    ilGenImages(1, &_imgId);
    ilBindImage(_imgId);
    if (ilLoadImage(_raw.texturePath.c_str()) != IL_TRUE)
    {
        exception::DevILException::handle("can't load image");
    }
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    if (width < _raw.size.x || height < _raw.size.y)
    {
        throw exception::Exception(exception::exId::DEVIL,
                                   exception::exType::CRITICAL,
                                   "requried size does not fit");
    }
    int ilImageMode = _raw.mode == channelMode::RGB ? IL_RGB : IL_RGBA;
    int glImageMode = _raw.mode == channelMode::RGB ? GL_RGB : GL_RGBA;
    PixelMap pixelMap{{_raw.size.x, _raw.size.y}, _raw.mode};
    ilCopyPixels(_raw.position.x,
                 _raw.position.y,
                 0,
                 _raw.size.x,
                 _raw.size.y,
                 1,
                 ilImageMode,
                 IL_UNSIGNED_BYTE,
                 pixelMap.data());

    DEBUG("Uploading texture to opengl");
    glGenTextures(1, &_glTextureId);
    glBindTexture(GL_TEXTURE_2D, _glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, glImageMode, width, height, 0, glImageMode, GL_UNSIGNED_BYTE, pixelMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    exception::OpenGLException::handle();
    DEBUG("Opengl texture is ready");

    ilDeleteImage(_imgId);
    ilBindImage(0);
    DEBUG("Read image of size " + std::to_string(width) + ' ' + std::to_string(height));

    exception::DevILException::handle();
}

GLuint Texture::getGlTextureId() const noexcept
{
    return _glTextureId;
}

GLint Texture::getWidth() const noexcept
{
    return _raw.size.x;
}

GLint Texture::getHeight() const noexcept
{
    return _raw.size.y;
}

Texture::~Texture()
{
    glDeleteTextures(1, &_glTextureId);
}

} // namespace ample::graphics
