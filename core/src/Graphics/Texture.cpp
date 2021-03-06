#define GL_GLEXT_PROTOTYPES 1

#include <GL/glu.h>
#include <algorithm>

#include "Debug.h"
#include "Exception.h"
#include "ILEnvironment.h"
#include "OpenGLEnvironment.h"
#include "Texture.h"

namespace ample::graphics
{
TextureRaw::TextureRaw(const std::string &texturePath,
                       const std::string &name,
                       const graphics::Vector2d<size_t> &eachSize,
                       const graphics::Vector2d<int> &startPosition,
                       const graphics::Vector2d<size_t> &framesCount,
                       const channelMode format,
                       const texturePlayback playback,
                       const size_t total,
                       const Vector2d<textureOrigin> &origin)
    : NamedObject(name, "Texture"),
      path(texturePath),
      eachSize(eachSize),
      startPosition(startPosition),
      framesCount(framesCount),
      format(format),
      playback(playback),
      total(!total ? framesCount.x * framesCount.y : total),
      origin(origin)
{
    if (total > framesCount.x * framesCount.y)
    {
        throw exception::Exception{exception::exId::DEVIL,
                                   exception::exType::CASUAL,
                                   "the number of frames exceeds the maximum"};
    }
}

inline size_t channelsCount(const channelMode &mode)
{
    return (mode == channelMode::RGB ? 3 : 4);
}

TextureRaw::TextureRaw(const Texture &other)
    : TextureRaw(other._raw) {}

Texture::PixelMap::Pixel::Pixel(channelMode format, uint8_t *data)
    : _data(data), _format(format) {}

Texture::PixelMap::Pixel &Texture::PixelMap::Pixel::operator=(const PixelMap::Pixel &other)
{
    _data[0] = other._data[0];
    _data[1] = other._data[1];
    _data[2] = other._data[2];
    if (_format == other._format && _format == channelMode::RGBA)
    {
        _data[3] = other._data[3];
    }
    if (_format == channelMode::RGBA && other._format == channelMode::RGB)
    {
        _data[3] = 0xFFu;
    }
    return *this;
}

Texture::PixelMap::PixelMapRow::PixelMapRow(channelMode format, uint8_t *data)
    : _data(data), _format(format) {}

Texture::PixelMap::Pixel Texture::PixelMap::PixelMapRow::operator[](const size_t i)
{
    return {_format, _data + i * channelsCount(_format)};
}

Texture::PixelMap::PixelMap(const graphics::Vector2d<size_t> &size,
                            const channelMode mode)
    : _size(size), _data(size.x * size.y * channelsCount(mode)), _format(mode)
{
    _rows.reserve(_size.y);
    for (size_t i = 0; i < _size.y; ++i)
    {
        _rows.emplace_back(_format, _data.data() + i * _size.x * channelsCount(_format));
    }
}

uint8_t *Texture::PixelMap::data()
{
    return _data.data();
}

size_t Texture::PixelMap::getWidth() const noexcept
{
    return _size.x;
}

size_t Texture::PixelMap::getHeight() const noexcept
{
    return _size.y;
}

Texture::PixelMap::PixelMapRow &Texture::PixelMap::operator[](const size_t i)
{
    return _rows[i];
}

Texture::GLSingleTexture::GLSingleTexture(PixelMap &pixels,
                                          const GLenum internalFormat,
                                          const GLenum format)
{
    glGenTextures(1, &_glTextureId);
    glBindTexture(GL_TEXTURE_2D, _glTextureId);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        internalFormat,
        pixels.getWidth(),
        pixels.getHeight(),
        0,
        format,
        GL_UNSIGNED_BYTE,
        pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    exception::OpenGLException::handle();
}

GLuint Texture::GLSingleTexture::glTextureId() const noexcept
{
    return _glTextureId;
}

Texture::GLSingleTexture::~GLSingleTexture()
{
    glDeleteTextures(1, &_glTextureId);
}

Texture::ILimage::ILimage(const std::string &imagePath,
                          ILenum format,
                          const Vector2d<size_t> &size,
                          const Vector2d<int> &position)
{
    ilGenImages(1, &_imgId);
    ilBindImage(_imgId);
    if (ilLoadImage(imagePath.c_str()) != IL_TRUE)
    {
        exception::DevILException::handle("can't load image");
    }
    ILuint realWidth = ilGetInteger(IL_IMAGE_WIDTH);
    ILuint realHeight = ilGetInteger(IL_IMAGE_HEIGHT);
    graphics::Vector2d<size_t> trueSize = size;
    if (!size.x || !size.y)
    {
        trueSize.x = realWidth;
        trueSize.y = realHeight;
    }
    if (realWidth < size.x || realHeight < size.y)
    {
        throw exception::DevILException{"requried size does not fit"};
    }
    _pixels = std::make_unique<PixelMap>(trueSize, format == IL_RGB ? channelMode::RGB : channelMode::RGBA);
    ilCopyPixels(position.x,
                 position.y,
                 0,
                 trueSize.x,
                 trueSize.y,
                 1,
                 format,
                 IL_UNSIGNED_BYTE,
                 _pixels->data());
    exception::DevILException::handle();
}

size_t Texture::ILimage::width() const noexcept
{
    return _pixels->getWidth();
}

size_t Texture::ILimage::height() const noexcept
{
    return _pixels->getHeight();
}

Texture::PixelMap &Texture::ILimage::pixels()
{
    return *_pixels;
}

Texture::ILimage::~ILimage()
{
    ilDeleteImage(_imgId);
    ilBindImage(0);
}

Texture::Texture(const TextureRaw &rawTexture)
    : NamedStoredObject(rawTexture.name(), "Texture"),
      _raw(rawTexture),
      _realPath(rawTexture.path)
{
    DEBUG("Loading texture " + _raw.path);
    os::environment::ILEnvironment::instance();

    ASSERT(GL_RGB == IL_RGB);
    ASSERT(GL_RGBA == IL_RGBA);

    GLenum glFormat = static_cast<GLenum>(_raw.format);
    ILenum ilFormat = static_cast<ILenum>(_raw.format);

    ILimage image{_raw.path,
                  ilFormat,
                  {
                      _raw.eachSize.x * _raw.framesCount.x,
                      _raw.eachSize.y * _raw.framesCount.y,
                  },
                  _raw.startPosition};

    DEBUG("Uploading texture to OpenGL");
    _frames.reserve(_raw.framesCount.x * _raw.framesCount.y);
    bool readAllFrames = false;
    _raw.eachSize = {image.width(), image.height()};

    for (size_t i = 0; i < _raw.framesCount.y; ++i)
    {
        for (size_t j = 0; j < _raw.framesCount.x && !readAllFrames; ++j)
        {
            PixelMap framePixels{_raw.eachSize, _raw.format};
            for (size_t pixelI = i * _raw.eachSize.y; pixelI < (i + 1) * _raw.eachSize.y; ++pixelI)
            {
                for (size_t pixelJ = j * _raw.eachSize.x; pixelJ < (j + 1) * _raw.eachSize.x; ++pixelJ)
                {
                    size_t frameI = pixelI - i * _raw.eachSize.y;
                    size_t frameJ = pixelJ - j * _raw.eachSize.x;
                    if (_raw.origin.x == textureOrigin::REVERSED)
                    {
                        frameI = _raw.eachSize.y - 1 - frameI;
                    }
                    if (_raw.origin.y == textureOrigin::REVERSED)
                    {
                        frameJ = _raw.eachSize.x - 1 - frameJ;
                    }
                    framePixels[frameI][frameJ] = image.pixels()[pixelI][pixelJ];
                }
            }
            _frames.emplace_back(framePixels, glFormat, glFormat);
            if (_frames.size() == _raw.total)
            {
                break;
            }
        }
    }
    DEBUG("OpenGL texture is ready");

    exception::DevILException::handle();
}

Texture::Texture(const filing::JsonIO &input)
    : Texture({input.read<std::string>("texture_path"),
               input.read<std::string>("name"),
               input.read<Vector2d<size_t>>("each_size"),
               input.read<Vector2d<int>>("start_position"),
               input.read<Vector2d<size_t>>("frames_count"),
               static_cast<channelMode>(input.read<int>("format")),
               static_cast<texturePlayback>(input.read<int>("playback")),
               input.read<size_t>("total"),
               Vector2d<textureOrigin>{
                   static_cast<textureOrigin>(input.read<Vector2d<int>>("origin").x),
                   static_cast<textureOrigin>(input.read<Vector2d<int>>("origin").y)}})
{
}

std::string Texture::dump()
{
    filing::JsonIO output{NamedStoredObject::dump()};
    output.write<std::string>("texture_path", _raw.path);
    output.write<graphics::Vector2d<size_t>>("each_size", _raw.eachSize);
    output.write<graphics::Vector2d<int>>("start_position", _raw.startPosition);
    output.write<graphics::Vector2d<size_t>>("frames_count", _raw.framesCount);
    output.write<int>("format", static_cast<int>(_raw.format));
    output.write<int>("playback", static_cast<int>(_raw.playback));
    output.write<size_t>("total", _raw.total);
    output.write<Vector2d<int>>("origin", {static_cast<int>(_raw.origin.x),
                                           static_cast<int>(_raw.origin.y)});
    if (_realPath != _raw.path)
    {
        std::filesystem::copy(_realPath, _raw.path);
    }
    return output;
}

void Texture::setPath(const std::string &path)
{
    _raw.path = std::filesystem::path(path) / (name() + std::filesystem::path(_raw.path).extension().string());
}

GLint Texture::getWidth() const noexcept
{
    return _raw.eachSize.x;
}

GLint Texture::getHeight() const noexcept
{
    return _raw.eachSize.y;
}

size_t Texture::getFramesTotal() const noexcept
{
    return _frames.size();
}

size_t Texture::getCurrentFrame() const noexcept
{
    return _currentFrame;
}

void Texture::setFrame(size_t num)
{
    if (num >= _raw.total)
    {
        throw exception::Exception{exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "the frame number exceeds their number"};
    }
    _currentFrame = num;
}
std::string &name() noexcept;

void Texture::pin() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, _frames[_currentFrame].glTextureId());
}

void Texture::unpin() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::nextFrame() noexcept
{
    switch (_raw.playback)
    {
    case texturePlayback::NORMAL:
        ++_currentFrame;
        if (_currentFrame == _raw.total)
        {
            _currentFrame = 0;
        }
        break;

    case texturePlayback::REVERSED:
        --_currentFrame;
        if (_currentFrame >= _raw.total)
        {
            _currentFrame = _raw.total - 1;
        }
        break;

    case texturePlayback::BOOMERANG:
        if (_boomerangAnimationForward)
        {
            ++_currentFrame;
            if (_currentFrame == _raw.total)
            {
                _currentFrame = _raw.total - 1;
                _boomerangAnimationForward = false;
            }
        }
        else
        {
            --_currentFrame;
            if (_currentFrame >= _raw.total)
            {
                _currentFrame = 0;
                _boomerangAnimationForward = true;
            }
        }
        break;

    default:
        break;
    }
}

const Texture::GLSingleTexture &Texture::getCurrentTexture() const
{
    return _frames[_currentFrame];
}

std::string Texture::path() const noexcept
{
    return _raw.path;
}
} // namespace ample::graphics
