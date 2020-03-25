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
                 const channelMode mode)
    : _texturePath(texturePath),
      _size(size),
      _position(position)
{
    DEBUG("Texture ctor");
    DEBUG("Size: ") << size.x << ' ' << size.y << std::endl;
    os::environment::ILEnvironment::instance();
    bool autoDetectSize = false;
    if (size.x == 0.0 && size.y == 0.0)
    {
        autoDetectSize = true;
    }
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
    int ilImageMode = mode == channelMode::RGB ? IL_RGB : IL_RGBA;
    int glImageMode = mode == channelMode::RGB ? GL_RGB : GL_RGBA;
    PixelMap pixelMap{{_size.x, _size.y}, mode};
    ilCopyPixels(position.x, position.y, 0, _size.x, _size.y, 1, ilImageMode,
                 IL_UNSIGNED_BYTE, pixelMap.data());
    DEBUG("Uploading texture to opengl");

    glGenTextures(1, &_glTextureId);
    DEBUG("Texture generated");
    glBindTexture(GL_TEXTURE_2D, _glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, glImageMode, width, height, 0, glImageMode, GL_UNSIGNED_BYTE, pixelMap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    exception::OpenGLException::handle();
    DEBUG("opengl texture is ready");

    ilDeleteImage(_imgId);
    ilBindImage(0);
    DEBUG("Read image of size") << width << ' ' << height << std::endl;

    exception::DevILException::handle();
}

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
