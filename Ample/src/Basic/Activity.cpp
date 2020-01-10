#include <cassert>
#include <exception>

#include "Activity.h"
#include "Storage.h"
#include "OsManager.h"
#include "EventHandler.h"
#include "EventManager.h"

namespace activity
{

int LogicBlock::init(Activity *activity)
{
    return 0;
}

Activity::Activity()
    : onRun(false){};

void Activity::onInitialization()
{
    return;
}

void Activity::onTermination()
{
    return;
}

basic::Storage Activity::onCreate()
{
    this->onInitialization();
    for (auto cond : this->conditions)
    {
        cond->init(this);
    }
    this->onRun = true;
    while (this->onRun)
    {
        this->onInput();
        this->updateConditions();
        this->onOutput();
    }
    this->onTermination();
    return this->storage;
}

void Activity::addLogicBlock(activity::LogicBlock *cond)
{
    if (!cond)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    conditions.push_back(cond);
}

void Activity::clearConditions()
{
    conditions.clear();
}

void Activity::stop()
{
    this->onRun = false;
}

void Activity::updateConditions()
{
    for (auto condition : this->conditions)
    {
        condition->update(this);
    }
}

QuitHandler::QuitHandler(Activity *windowActivity)
    : activity(windowActivity) {}

void QuitHandler::handleEvent(const SDL_Event &event)
{
    activity->stop();
}

WindowActivity::WindowActivity(os::Window *window)
    : Activity(),
      eventManager(new control::EventManager),
      window(window),
      clock(new os::Clock),
      quitHandler(new QuitHandler(this))
{
    this->eventManager->addEventHandler(SDL_QUIT, this->quitHandler);
}

void WindowActivity::onInitialization()
{
    this->window->open();
}

void WindowActivity::onTermination()
{
    this->window->close();
}

void WindowActivity::onInput()
{
    eventManager->update();
    clock->update();
}

void WindowActivity::onOutput()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    this->window->refresh();
}

WindowActivity::~WindowActivity()
{
    delete quitHandler;
    delete eventManager;
    delete clock;
}
} // namespace activity
