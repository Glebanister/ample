#pragma once

#include <vector>

#include "Storage.h"
#include "EventManager.h"
#include "EventHandler.h"
#include "Window.h"
#include "Clock.h"

namespace activity
{

class Activity;

class LogicBlock
{
public:
    virtual void onInitialization();
    virtual void onUpdate() = 0;
    virtual void onTermination();

    virtual ~LogicBlock() = default;
};

class Activity
{
public:
    Activity();

    void start();
    void stop();

    void addLogicBlock(activity::LogicBlock *cond);
    void clearLogicBlocks();

protected:
    virtual void init();
    virtual void input();
    virtual void update();
    virtual void output();
    virtual void terminate();

    virtual bool onStart();
    virtual void onInitialization();
    virtual void onInput();
    virtual void onUpdate();
    virtual void onOutput();
    virtual bool onStop();
    virtual void onTermination();

    bool _onRun;
    std::vector<activity::LogicBlock *> _conditions;
};

class QuitHandler : public control::EventHandler
{
public:
    QuitHandler() = delete;
    QuitHandler(Activity *windowActivity);

    void handleEvent(const SDL_Event &event) override;

private:
    Activity *_activity;
};

class WindowActivity;

class WindowEventHandler : public control::EventHandler
{
public:
    WindowEventHandler() = delete;
    WindowEventHandler(WindowActivity *activity, os::Window *window);

    void handleEvent(const SDL_Event &event) override;

private:
    os::Window *_window;
    WindowActivity *_activity;
};

class WindowActivity : public Activity
{
public:
    control::EventManager *eventManager;

    WindowActivity() = delete;
    WindowActivity(os::Window *window);

    WindowActivity(const WindowActivity &other) = delete;
    WindowActivity &operator=(const WindowActivity &other) = delete;

    virtual ~WindowActivity();

protected:
    virtual void init() override;
    virtual void input() override;
    virtual void terminate() override;

    virtual void onResize();

    os::Window *_window;
    os::Clock *_clock;
    QuitHandler *_quitHandler;
    WindowEventHandler *_windowEventHandler;

    friend void activity::WindowEventHandler::handleEvent(const SDL_Event &event);
};
} // namespace activity
