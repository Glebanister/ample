#include "WindowActivity.h"

namespace window
{
QuitHandler::QuitHandler(ample::Activity *windowActivity)
    : activity(windowActivity) {}

void QuitHandler::handleEvent(const SDL_Event &event)
{
    activity->stop();
}

WindowActivity::WindowActivity(Window *window)
    : ample::Activity(),
      eventManager(new control::EventManager),
      window(window),
      quitHandler(new QuitHandler(this))
{
    this->eventManager->addEventHandler(SDL_QUIT, this->quitHandler);
}

void WindowActivity::init()
{
    this->window->open();
}

void WindowActivity::processInput()
{
    eventManager->update();
}

void WindowActivity::generateOutput()
{
    return;
}

WindowActivity::~WindowActivity()
{
    delete quitHandler;
    delete eventManager;
}
} // namespace window
