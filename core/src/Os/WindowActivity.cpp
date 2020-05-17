#include <GL/gl.h>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Exception.h"
#include "OpenGLEnvironment.h"
#include "ShaderProcessor.h"
#include "WindowActivity.h"

namespace ample::window
{
QuitHandler::QuitHandler(activity::Activity &windowActivity)
    : _activity(windowActivity) {}

void QuitHandler::handleEvent(const SDL_Event &)
{
    _activity.kill();
}

WindowEventHandler::WindowEventHandler(WindowActivity &activity, Window &window)
    : _window(window), _activity(activity) {}

void WindowEventHandler::handleEvent(const SDL_Event &event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        _window.resize(event.window.data1, event.window.data2);
        _activity.onResize();
    }
}

WindowActivity::WindowActivity(const std::string &name,
                               const pixel_t &x,
                               const pixel_t &y,
                               const pixel_t &width,
                               const pixel_t &height,
                               const uint32_t &posFlags,
                               const uint32_t &modeFlags)
    : _window(name, x, y, width, height, posFlags, modeFlags)
{
    control::EventManager::instance().addEventHandler(SDL_QUIT, std::make_shared<QuitHandler>(*this));
    control::EventManager::instance().addEventHandler(SDL_WINDOWEVENT, std::make_shared<WindowEventHandler>(*this, _window));
    time::Clock::init();

    os::environment::OpenGLEnvironment::instance();
    time::Clock::update();
    this->_window.swapBuffer();
    control::EventManager::instance().update();
}

void WindowActivity::onActive()
{
    activity::Activity::onActive();
    time::Clock::update();
    control::EventManager::instance().update();
}

pixel_t WindowActivity::getWidth() const
{
    return _window.getWidth();
}

pixel_t WindowActivity::getHeight() const
{
    return _window.getHeight();
}

void WindowActivity::onResize() {}

Window &WindowActivity::osWindow()
{
    return _window;
}
} // namespace ample::window
