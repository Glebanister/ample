#include <cassert>
#include <exception>

#include "Activity.h"
#include "OsManager.h"
#include "EventHandler.h"
#include "EventManager.h"
#include "Error.h"
#include "Utils.h"

namespace activity
{

void LogicBlock::onInitialization() {}
void LogicBlock::onTermination() {}

Activity::Activity()
    : _onRun(false){}

bool Activity::onStart() { return true; }
void Activity::onInitialization() {}
void Activity::onInput() {}
void Activity::onUpdate() {}
void Activity::onOutput() {}
bool Activity::onStop() { return true; }
void Activity::onTermination() {}

void Activity::init()
{
    for (auto block : _conditions)
    {
        block->onInitialization();
    }
    onInitialization();
}

void Activity::input()
{
    onInput();
    return;
}

void Activity::update()
{
    for (auto block : _conditions)
    {
        block->onUpdate();
    }
    onUpdate();
    return;
}

void Activity::output()
{
    onOutput();
}

void Activity::terminate()
{
    onTermination();
    return;
}

void Activity::stop()
{
    if (onStop())
    {
        _onRun = false;
    }
}

void Activity::start()
{
    if (!onStart())
    {
        return;
    }
    init();
    _onRun = true;
    while (_onRun)
    {
        input();
        update();
        output();
    }
    terminate();
}

void Activity::addLogicBlock(activity::LogicBlock *block)
{
    if (!block)
    {
        throw exception::Exception(
            exception::exId::NULLPTR,
            exception::exType::CRITICAL);
    }
    _conditions.push_back(block);
}

void Activity::clearLogicBlocks()
{
    _conditions.clear();
}

QuitHandler::QuitHandler(Activity *windowActivity)
    : _activity(windowActivity) {}

void QuitHandler::handleEvent(const SDL_Event &event)
{
    ignore(event);
    _activity->stop();
}

WindowEventHandler::WindowEventHandler(WindowActivity *activity, os::Window *window)
    : _window(window), _activity(activity) {}

void WindowEventHandler::handleEvent(const SDL_Event &event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        _window->resize(event.window.data1, event.window.data2);
        _activity->onResize();
    }
}

WindowActivity::WindowActivity(os::Window *window)
    : Activity(),
      eventManager(new control::EventManager),
      _window(window),
      _clock(new os::Clock),
      _quitHandler(new QuitHandler(this)),
      _windowEventHandler(new WindowEventHandler(this, _window))
{
    eventManager->addEventHandler(SDL_QUIT, _quitHandler);
    eventManager->addEventHandler(SDL_WINDOWEVENT, _windowEventHandler);
}

void WindowActivity::init()
{
    _window->open();
    for (auto block : _conditions)
    {
        block->onInitialization();
    }
    onInitialization();
}

void WindowActivity::input()
{
    eventManager->update();
    _clock->update();
    onInput();
}

void WindowActivity::terminate()
{
    _window->close();
    onTermination();
}

void WindowActivity::onResize()
{
    return;
}

WindowActivity::~WindowActivity()
{
    delete eventManager;
    delete _windowEventHandler;
    delete _quitHandler;
    delete _clock;
}
} // namespace activity
