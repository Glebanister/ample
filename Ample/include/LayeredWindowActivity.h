#pragma once

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "WindowObject.h"
#include "Activity.h"

namespace graphics
{
class Layer
{
public:
    virtual void init();
    virtual void draw();
    virtual void terminate();

    void addObject(WindowObject *obj);

    void deleteAllObjects();

protected:
    virtual void onInitialization();
    virtual void onDraw();
    virtual void onTermination();
    std::vector<WindowObject *> _objects;
};

class Layer2d : public Layer
{
public:
    Layer2d() = delete;
    Layer2d(const int w, const int h);

    void init() override;

private:
    int _w, _h;
};

class LayeredWindowActivity : public activity::WindowActivity
{
public:
    LayeredWindowActivity(os::Window *window);

    void addLayer(Layer *layer);
    void clearLayers();

    virtual void init() override;
    virtual void output() override;
    virtual void terminate() override;

private:
    std::vector<Layer *> _layers;
};
} // namespace graphics
