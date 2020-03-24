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
class Texture final : public utils::Noncopyable
{
private:
    enum class channelMode
    {
        RGB,
        RGBA,
    };

    class PixelMap
    {
    public:
        PixelMap(const graphics::Vector2d<int> &size,
                 const channelMode mode = channelMode::RGB);
        PixelMap() = default;
        PixelMap &operator=(const PixelMap &) = default;

        uint8_t *data();
        void resize(const graphics::Vector2d<int> &size);
        int getWidth() const noexcept;
        int getHeight() const noexcept;

    private:
        std::vector<uint8_t> _data;
        graphics::Vector2d<int> _size;
    };

public:
    Texture(const std::string &texturePath,
            const graphics::Vector2d<int> size,
            const graphics::Vector2d<int> position);
    Texture(const std::string &texturePath,
            const graphics::Vector2d<int> size);
    Texture(const std::string &texturePath);

    ~Texture();

    GLuint getGlTextureId() const noexcept;
    GLint getWidth() const noexcept;
    GLint getHeight() const noexcept;

private:
    Texture(const std::string &texturePath,
            const graphics::Vector2d<int> size,
            const graphics::Vector2d<int> position,
            const bool autoDetectSize);

    const std::string &_texturePath;
    graphics::Vector2d<int> _size;
    graphics::Vector2d<int> _position;
    ILuint _imgId;
    GLuint _glTextureId;
};
} // namespace ample::graphics
