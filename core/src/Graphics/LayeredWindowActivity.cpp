#include "LayeredWindowActivity.h"

namespace ample::graphics
{
LayeredWindowActivity::LayeredWindowActivity(const std::string &name,
                                             const pixel_t &x,
                                             const pixel_t &y,
                                             const pixel_t &width,
                                             const pixel_t &height,
                                             const uint32_t &posFlags,
                                             const uint32_t &modeFlags)
    : WindowActivity(name, x, y, width, height, posFlags, modeFlags)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics::shaders::ShaderProcessor::instance().use();
}

void LayeredWindowActivity::addLayer(std::shared_ptr<Layer> layer)
{
    Activity::addBehavior(std::static_pointer_cast<Behavior>(layer));
    _layers.push_back(layer);
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
    auto color = os::environment::OpenGLEnvironment::instance().getColor();
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    graphics::shaders::ShaderProcessor::instance().use();
    WindowActivity::onActive();
}
} // namespace ample::graphics
