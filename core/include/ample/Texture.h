#pragma once

#define GL_GLEXT_PROTOTYPES 1

#include <IL/il.h>
#include <IL/ilu.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include <filesystem>
#include <cstddef>

#include "Vector2d.h"
#include "Noncopyable.h"
#include "NamedStoredObject.h"

namespace ample::graphics
{
enum class channelMode
{
    RGB = IL_RGB,
    RGBA = IL_RGBA,
};

enum class texturePlayback
{
    NORMAL,
    REVERSED,
    BOOMERANG,
};

enum class textureOrigin
{
    NORMAL,
    REVERSED,
};

class Texture;

class TextureRaw : public filing::NamedObject
{
public:
    TextureRaw(const std::string &texturePath,
               const std::string &name,
               const graphics::Vector2d<size_t> &eachSize,
               const graphics::Vector2d<int> &startPosition,
               const graphics::Vector2d<size_t> &framesCount,
               const channelMode format,
               const texturePlayback playback,
               const size_t total = 0UL,
               const Vector2d<textureOrigin> &origin = {textureOrigin::NORMAL, textureOrigin::NORMAL});

    TextureRaw(const Texture &);

public:
    std::string path;
    graphics::Vector2d<size_t> eachSize;
    graphics::Vector2d<int> startPosition;
    graphics::Vector2d<size_t> framesCount;
    channelMode format;
    texturePlayback playback;
    size_t total;
    Vector2d<textureOrigin> origin;
};

class Texture final : public utils::Noncopyable, public filing::NamedStoredObject
{
private:
    class PixelMap
    {
    public:
        class Pixel
        {
        public:
            Pixel(channelMode, uint8_t *data);
            Pixel(const Pixel &) = delete;
            Pixel &operator=(const Pixel &);

        private:
            uint8_t *_data;
            const channelMode _format;
        };

        class PixelMapRow
        {
        public:
            PixelMapRow(channelMode, uint8_t *data);
            Pixel operator[](const size_t);

        private:
            uint8_t *_data;
            const channelMode _format;
        };

        PixelMap(const graphics::Vector2d<size_t> &size,
                 const channelMode mode);

        uint8_t *data();
        size_t getWidth() const noexcept;
        size_t getHeight() const noexcept;

        PixelMapRow &operator[](const size_t);

    private:
        std::vector<PixelMapRow> _rows;
        graphics::Vector2d<size_t> _size;
        std::vector<uint8_t> _data;
        const channelMode _format;
    };

    class ILimage final
    {
    public:
        ILimage(const std::string &imagePath,
                ILenum format,
                const Vector2d<size_t> &size,
                const Vector2d<int> &position);
        ~ILimage();

        PixelMap &pixels();

        size_t width() const noexcept;
        size_t height() const noexcept;

    private:
        ILuint _imgId;
        std::unique_ptr<PixelMap> _pixels;
    };

    class GLSingleTexture final
    {
    public:
        GLSingleTexture(PixelMap &pixels,
                        const GLenum internalFormat,
                        const GLenum format);

        GLuint glTextureId() const noexcept;

        ~GLSingleTexture();

    private:
        GLuint _glTextureId;
    };

public:
    Texture(const TextureRaw &rawTexture);
    Texture(const filing::JsonIO &input);
    std::string dump() override;

    GLint getWidth() const noexcept;
    GLint getHeight() const noexcept;

    size_t getFramesTotal() const noexcept;
    size_t getCurrentFrame() const noexcept;
    void setFrame(size_t num);
    void nextFrame() noexcept;

    void pin() const noexcept;
    void unpin() const noexcept;
    const GLSingleTexture &getCurrentTexture() const;

    std::string path() const noexcept;

    void setPath(const std::string &path);

private:
    TextureRaw _raw;
    std::vector<GLSingleTexture> _frames;
    size_t _currentFrame = 0U;
    friend class TextureRaw;
    bool _boomerangAnimationForward = true;
    std::string _realPath;
};
} // namespace ample::graphics
