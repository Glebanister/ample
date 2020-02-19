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
        Viewport(pixel_t xv, pixel_t yv, pixel_t wv, pixel_t hv);
        Viewport(pixel_t wv, pixel_t hv);
        void set();
    };

public:
    Camera(pixel_t xView, pixel_t yView, pixel_t wView, pixel_t hView);
    Camera(pixel_t wView, pixel_t hView);

    virtual void look() = 0;
    virtual void unlook() = 0;
    void setViewport(const Viewport &viewport);
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
