#pragma once

#include <SDL2/SDL.h>

#include "EventHandler.h"
#include "EventManager.h"
#include "Activity.h"
#include "Window.h"

namespace window
{

class QuitHandler : public control::EventHandler
{
public:
    QuitHandler() = delete;
    QuitHandler(ample::Activity *windowActivity);

    void handleEvent(const SDL_Event &event) override;

private:
    ample::Activity *activity;
};

class WindowActivity : public ample::Activity
{
public:
    control::EventManager *eventManager;

    WindowActivity() = delete;
    WindowActivity(Window *window);

    virtual void init() override;

    virtual void terminate() override;

    virtual void processInput() override;

    virtual void generateOutput() override;

    WindowActivity(const WindowActivity &other) = delete;
    WindowActivity &operator=(const WindowActivity &other) = delete;

    virtual ~WindowActivity();

protected:
    Window *window;
    QuitHandler *quitHandler;
};
} // namespace window
