#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(window::Window &window)
    : WindowActivity(window)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics::shaders::ShaderProcessor::instance().use();
}

void LayeredWindowActivity::addLayer(Layer &layer)
{
    Activity::addBehaviour(layer);
    _layers.push_back(&layer);
}

void LayeredWindowActivity::cleanLayers()
{
    _layers.clear();
}

void LayeredWindowActivity::onAwake()
{
    WindowActivity::onAwake();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics::shaders::ShaderProcessor::instance().use();
}

void LayeredWindowActivity::onActive()
{
    this->_window.swapBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics::shaders::ShaderProcessor::instance().use();
    WindowActivity::onActive();
}
} // namespace ample::graphics
