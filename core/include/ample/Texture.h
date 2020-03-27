#pragma once

#define GL_GLEXT_PROTOTYPES 1

#include <IL/il.h>
#include <IL/ilu.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <cstddef>

#include "Vector2d.h"
#include "Noncopyable.h"

namespace ample::graphics
{
enum class channelMode
{
    RGB,
    RGBA,
};

class Texture;

class TextureRaw
{
public:
    TextureRaw(const std::string &texturePath,
               const graphics::Vector2d<int> &size,
               const graphics::Vector2d<int> &position,
               const channelMode mode);

    TextureRaw(const Texture &);

public:
    const std::string &texturePath;
    graphics::Vector2d<int> size;
    graphics::Vector2d<int> position;
    channelMode mode;
};

class Texture final : public utils::Noncopyable
{
private:
    class PixelMap
    {
    public:
        PixelMap(const graphics::Vector2d<int> &size,
                 const channelMode mode = channelMode::RGB);
        PixelMap() = default;

        uint8_t *data();
        void resize(const graphics::Vector2d<int> &size);
        int getWidth() const noexcept;
        int getHeight() const noexcept;

    private:
        std::vector<uint8_t> _data;
        graphics::Vector2d<int> _size;
    };

public:
    Texture(const TextureRaw &rawTexture);

    ~Texture();

    GLuint getGlTextureId() const noexcept;
    GLint getWidth() const noexcept;
    GLint getHeight() const noexcept;

private:
    TextureRaw _raw;
    ILuint _imgId;
    GLuint _glTextureId;

    friend class TextureRaw;
};
} // namespace ample::graphics
