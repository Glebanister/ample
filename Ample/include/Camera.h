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
        Viewport(); // TODO: remove this
        void set();
    };

public:
    virtual void look() = 0;
    virtual void unlook() = 0;
    void setViewport(const Viewport &viewport);

protected:
    Viewport _viewport;
};
} // namespace ample::graphics
