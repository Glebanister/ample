#include <GL/gl.h>
#include <stdexcept>
#include <cassert>
#include <iostream>

#include "WindowActivity.h"
#include "Exception.h"

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
    : eventManager(std::make_shared<control::EventManager>(window)),
      _window(window),
      _quitHandler(std::make_shared<QuitHandler>(*this)),
      _windowEventHandler(std::make_shared<WindowEventHandler>(*this, _window))
{
    eventManager->addEventHandler(SDL_QUIT, _quitHandler);
    eventManager->addEventHandler(SDL_WINDOWEVENT, _windowEventHandler);
}

void WindowActivity::onActive()
{
    activity::Activity::onActive();
    time::Clock::update();
    eventManager->update();
    this->_window.swapBuffer();
    glClearColor(20.0 / 256.0, 60.0 / 256.0, 80.0 / 256.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
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
} // namespace ample::window
