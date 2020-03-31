#include <GL/gl.h>
#include <stdexcept>
#include <cassert>
#include <iostream>

#include "WindowActivity.h"
#include "Exception.h"
#include "ShaderProcessor.h"
#include "OpenGLEnvironment.h"

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

WindowActivity::WindowActivity(Window &window)
    : _eventManager(std::make_shared<control::EventManager>(window)),
      _window(window),
      _quitHandler(std::make_shared<QuitHandler>(*this)),
      _windowEventHandler(std::make_shared<WindowEventHandler>(*this, _window))
{
    _eventManager->addEventHandler(SDL_QUIT, *_quitHandler);
    _eventManager->addEventHandler(SDL_WINDOWEVENT, *_windowEventHandler);
    time::Clock::init();

    os::environment::OpenGLEnvironment::instance();
    time::Clock::update();
    this->_window.swapBuffer();
    _eventManager->update();
}

void WindowActivity::onActive()
{
    activity::Activity::onActive();
    time::Clock::update();
    _eventManager->update();
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

control::EventManager &WindowActivity::eventManager() noexcept
{
    return *_eventManager;
}

Window &WindowActivity::osWindow()
{
    return _window;
}
} // namespace ample::window
