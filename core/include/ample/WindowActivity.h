#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <memory>

#include "Activity.h"
#include "Window.h"
#include "ShaderProcessor.h"

namespace ample::window
{
class QuitHandler : public control::EventHandler
{
public:
    QuitHandler() = delete;
    QuitHandler(activity::Activity &windowActivity);

    void handleEvent(const SDL_Event &event) override;

private:
    activity::Activity &_activity;
};

class WindowActivity;

class WindowEventHandler : public control::EventHandler
{
public:
    WindowEventHandler() = delete;
    WindowEventHandler(WindowActivity &windowActivity,
                       Window &window);

    void handleEvent(const SDL_Event &event) override;

private:
    Window &_window;
    WindowActivity &_activity;
};

class WindowActivity : public activity::Activity
{
public:
    std::shared_ptr<control::EventManager> eventManager;

    WindowActivity() = delete;
    WindowActivity(Window &window);

    WindowActivity(const WindowActivity &other) = delete;

    pixel_t getWidth() const;
    pixel_t getHeight() const;

    virtual void onActive() override;

protected:
    virtual void onResize();


    Window &_window;
    std::shared_ptr<QuitHandler> _quitHandler;
    std::shared_ptr<WindowEventHandler> _windowEventHandler;

    friend void WindowEventHandler::handleEvent(const SDL_Event &event);
};
} // namespace ample::window
