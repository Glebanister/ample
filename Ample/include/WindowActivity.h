#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <memory>

#include "Activity.h"

namespace ample::window
{
typedef double pixel_t;

enum winpos : uint32_t
{
    UNDEFINED_POS = 0b0,
    CENTERED_X = 0b1,
    CENTERED_Y = 0b10,
};

enum winmode : uint32_t
{
    UNDEFINED_MODE = 0,
    FULLSCREEN = SDL_WINDOW_FULLSCREEN,
    BORDERLESS = SDL_WINDOW_BORDERLESS,
    RESIZABLE = SDL_WINDOW_RESIZABLE,
    MAXIMIZED = SDL_WINDOW_MAXIMIZED,
    MINIMIZED = SDL_WINDOW_MINIMIZED,
};

class Window final
{
public:
    Window() = delete;

    Window(const std::string &name,
           const pixel_t &x,
           const pixel_t &y,
           const pixel_t &width,
           const pixel_t &height,
           const uint32_t &posFlags,
           const uint32_t &modeFlags);

    Window(const Window &other) = delete;
    Window &operator=(const Window &) = delete;

    void swapBuffer();

    pixel_t getWidth() const;
    pixel_t getHeight() const;

    void resize(const pixel_t w, const pixel_t &h);

    ~Window();

private:
    SDL_Window *_winPtr = nullptr;
    std::string _name;
    pixel_t _x, _y;
    pixel_t _width, _height;
    uint32_t _modeFlags;
    SDL_GLContext _glContext;
};

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
    std::unique_ptr<control::EventManager> eventManager;

    WindowActivity() = delete;
    WindowActivity(Window &window);

    WindowActivity(const WindowActivity &other) = delete;

    pixel_t getWidth() const;
    pixel_t getHeight() const;

protected:
    virtual void onResize();

    virtual void onAwake() override;
    virtual void onActive() override;
    virtual void onDestroy() override;

    Window &_window;
    std::unique_ptr<QuitHandler> _quitHandler;
    std::unique_ptr<WindowEventHandler> _windowEventHandler;

    friend void WindowEventHandler::handleEvent(const SDL_Event &event);
};
} // namespace ample::window
