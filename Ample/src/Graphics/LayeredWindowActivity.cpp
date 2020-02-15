#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

#include "WindowObject.h"
#include "Activity.h"
#include "LayeredWindowActivity.h"

namespace graphics
{
void Layer::onInitialization() {}
void Layer::onDraw() {}
void Layer::onTermination() {}

void Layer::init()
{
    return;
}

void Layer::terminate()
{
    return;
}

void Layer::draw()
{
    onDraw();
    for (auto obj : _objects)
    {
        obj->draw();
    }
}

void Layer::addObject(WindowObject *obj)
{
    _objects.push_back(obj);
}

void Layer::deleteAllObjects()
{
    _objects.clear();
}

Layer2d::Layer2d(const int w, const int h)
    : _w(w), _h(h) {}

void Layer2d::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, _w, _h, 0.f, 0.f, 1.f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
}

LayeredWindowActivity::LayeredWindowActivity(os::Window *window)
    : activity::WindowActivity(window) {}

void LayeredWindowActivity::init()
{
    _window->open();
    for (auto layer : _layers)
    {
        layer->init();
    }
    for (auto block : _conditions)
    {
        block->onInitialization();
    }
    onInitialization();
}

void LayeredWindowActivity::output()
{
    glClearColor(0.2, 0.2, 0.2, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto layer : _layers)
    {
        layer->draw();
    }
    _window->swapBuffer();

    onOutput();
}

void LayeredWindowActivity::terminate()
{
    for (auto layer : _layers)
    {
        layer->terminate();
    }
    _window->close();
    for (auto block : _conditions)
    {
        block->onTermination();
    }
    for (auto block : _conditions)
    {
        block->onTermination();
    }
    onTermination();
}

void LayeredWindowActivity::addLayer(Layer *layer)
{
    _layers.push_back(layer);
}

void LayeredWindowActivity::clearLayers()
{
    _layers.clear();
}
} // namespace graphics
