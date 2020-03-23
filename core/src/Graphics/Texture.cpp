#include <GL/glu.h>

#include "Texture.h"
#include "Exception.h"
#include "Debug.h"
#include "ILEnvironment.h"
#include "OpenGLEnvironment.h"

namespace ample::graphics
{
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

void Texture::PixelMap::debug() const noexcept
{
    for (int i = 0; i < _size.y; ++i)
    {
        for (int j = 0; j < _size.x; ++j)
        {
            std::cout << (int)_data[i * _size.x * 3 + j * 3] << ' '
                      << (int)_data[i * _size.x * 3 + j * 3 + 1] << ' '
                      << (int)_data[i * _size.x * 3 + j * 3 + 2] << ' '
                      << std::endl;
        }
    }
}

int Texture::PixelMap::getWidth() const noexcept
{
    return _size.x;
}

int Texture::PixelMap::getHeight() const noexcept
{
    return _size.y;
}

Texture::Texture(const std::string &texturePath,
                 const graphics::Vector2d<int> size,
                 const graphics::Vector2d<int> position,
                 const bool autoDetectSize)
    : _texturePath(texturePath),
      _size(size),
      _position(position)
{
    os::environment::ILEnvironment::instance();
    DEBUG("Loading texture " + texturePath);

    ilGenImages(1, &_imgId);
    ilBindImage(_imgId);
    if (ilLoadImage(texturePath.c_str()) != IL_TRUE)
    {
        exception::DevILException::handle("can't load image");
    }
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    if (autoDetectSize)
    {
        _size = {width, height};
    }
    if (width < size.x || height < size.y)
    {
        throw exception::Exception(exception::exId::DEVIL,
                                   exception::exType::CRITICAL,
                                   "requried size does not fit");
    }
    PixelMap pixelMap{{width, height}, channelMode::RGB};
    ilCopyPixels(position.x, position.y, 0, width, height, 1, IL_RGB,
                 IL_UNSIGNED_BYTE, pixelMap.data());
    DEBUG("Uploading texture to opengl");

    glGenTextures(1, &_glTextureId);
    DEBUG("Texture generated");
    glBindTexture(GL_TEXTURE_2D, _glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelMap.data());
    DEBUG("Texture uploaded");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    DEBUG("Texture parametrized");
    exception::OpenGLException::handle();
    DEBUG("opengl texture is ready");

    ilDeleteImage(_imgId);
    ilBindImage(0);
    DEBUG("Read image of size") << width << ' ' << height << std::endl;

    exception::DevILException::handle();
}

Texture::Texture(const std::string &texturePath,
                 const graphics::Vector2d<int> size,
                 const graphics::Vector2d<int> position)
    : Texture(texturePath, size, position, false) {}

Texture::Texture(const std::string &texturePath,
                 const graphics::Vector2d<int> size)
    : Texture(texturePath, size, {0, 0}, false) {}

Texture::Texture(const std::string &texturePath)
    : Texture(texturePath, {0, 0}, {0, 0}, true) {}

GLuint Texture::getGlTextureId() const noexcept
{
    return _glTextureId;
}

GLint Texture::getWidth() const noexcept
{
    return _size.x;
}

GLint Texture::getHeight() const noexcept
{
    return _size.y;
}

Texture::~Texture()
{
    glDeleteTextures(1, &_glTextureId);
}

} // namespace ample::graphics
