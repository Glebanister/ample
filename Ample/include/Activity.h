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
    virtual int init(Activity *);
    virtual int update(Activity *) = 0;
};

class Activity
{
public:
    Activity();

    virtual basic::Storage start();
    void stop();

    void addLogicBlock(activity::LogicBlock *cond);
    void clearConditions();

protected:
    virtual void onInitialization();
    virtual void onTermination();

    virtual void onInput() = 0;
    virtual void onOutput() = 0;

    virtual void updateConditions();

    bool onRun;
    std::vector<activity::LogicBlock *> conditions;
    basic::Storage storage;
};

class QuitHandler : public control::EventHandler
{
public:
    QuitHandler() = delete;
    QuitHandler(Activity *windowActivity);

    void handleEvent(const SDL_Event &event) override;

private:
    Activity *activity;
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
    virtual void onInitialization() override;
    virtual void onTermination() override;

    virtual void onInput() override;
    virtual void onOutput() override;

    os::Window *window;
    os::Clock *clock;
    QuitHandler *quitHandler;
};
} // namespace activity
