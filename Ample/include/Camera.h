#pragma once

#include "Vector2d.h"

namespace ample::graphics
{
using pixel_t = double;

class Camera
{
protected:
    struct Viewport final
    {
        Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv);
        Viewport(pixel_t wv, pixel_t hv);
        
        void set();
        
        Vector2d<pixel_t> size;
        Vector2d<pixel_t> position;
    };

public:
    Camera(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView);
    Camera(pixel_t wView, pixel_t hView);

    virtual void look() = 0;
    virtual void unlook() = 0;
    void setViewport(pixel_t x, pixel_t y, pixel_t w, pixel_t h);
    void setViewport(pixel_t w, pixel_t h);

    pixel_t getViewportX() const;
    pixel_t getViewportY() const;
    pixel_t getViewportW() const;
    pixel_t getViewportH() const;

protected:
    Viewport _viewport;
};
} // namespace ample::graphics
