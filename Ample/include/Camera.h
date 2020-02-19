#pragma once

namespace ample::graphics
{
typedef double pixel_t;

class Camera
{
protected:
    struct Viewport final
    {
        pixel_t x, y, w, h;
        Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv); // TODO: w, h constructor
        Viewport(pixel_t wv, pixel_t hv);
        Viewport(const Viewport &) = default;
        void set();
        Viewport &operator=(const Viewport &) = default;
    };

public:
    virtual void look() = 0;
    virtual void unlook() = 0;
    void setViewport(const Viewport &viewport);
    void setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h);
    void setViewport(pixel_t w, pixel_t h);

protected:
    Viewport _viewport;
};
} // namespace ample::graphics
