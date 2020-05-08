#pragma once

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <memory>
#include <string>

#include "Activity.h"
#include "ShaderProcessor.h"
#include "Window.h"

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
    WindowActivity(const std::string &name,
                   const pixel_t &x,
                   const pixel_t &y,
                   const pixel_t &width,
                   const pixel_t &height,
                   const uint32_t &posFlags,
                   const uint32_t &modeFlags);

    pixel_t getWidth() const;
    pixel_t getHeight() const;

    virtual void onActive() override;

    Window &osWindow();

protected:
    virtual void onResize();

    Window _window;

    friend void WindowEventHandler::handleEvent(const SDL_Event &event);
};
} // namespace ample::window
