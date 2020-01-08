#include <GL/gl.h>

#include "WindowActivity.h"
#include "Window.h"

#include <iostream>

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

void WindowActivity::terminate()
{
    this->window->close();
}

void WindowActivity::processInput()
{
    eventManager->update();
}

void WindowActivity::generateOutput()
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
}
} // namespace window
