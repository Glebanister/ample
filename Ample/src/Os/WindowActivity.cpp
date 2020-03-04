#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <stdexcept>
#include <cassert>
#include <iostream>

#include "WindowActivity.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::window
{
QuitHandler::QuitHandler(activity::Activity &windowActivity)
    : _activity(windowActivity) {}

void QuitHandler::handleEvent(const SDL_Event &)
{
    _activity.kill();
}

WindowEventHandler::WindowEventHandler(WindowActivity &activity, Window &window)
    : _window(window), _activity(activity) {}

void WindowEventHandler::handleEvent(const SDL_Event &event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        _window.resize(event.window.data1, event.window.data2);
        _activity.onResize();
    }
}

WindowActivity::WindowActivity(Window &window)
    : eventManager(std::make_shared<control::EventManager>(window)),
      _window(window),
      _quitHandler(std::make_shared<QuitHandler>(*this)),
      _windowEventHandler(std::make_shared<WindowEventHandler>(*this, _window)),
      _shadersProcessor(std::make_unique<graphics::shaders::ShaderProcessor>())
{
    eventManager->addEventHandler(SDL_QUIT, *_quitHandler);
    eventManager->addEventHandler(SDL_WINDOWEVENT, *_windowEventHandler);
    time::Clock::init();

    _shadersProcessor->addShader(ample::graphics::shaders::shaderType::VERTEX, "../../Ample/src/Graphics/Shaders/Shaders/BasicVertexShader.vert");
    _shadersProcessor->addShader(ample::graphics::shaders::shaderType::FRAGMENT, "../../Ample/src/Graphics/Shaders/Shaders/BasicFragmentShader.frag");
    _shadersProcessor->link();

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glPolygonMode(GL_FRONT | GL_BACK, GL_FILL);
    glClearColor(20.0 / 256.0, 60.0 / 256.0, 80.0 / 256.0, 0.5);
    DEBUG("Generating vertex array");
    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);
    exception::OpenGLException::handle();
}

void WindowActivity::onActive()
{
    activity::Activity::onActive();
    time::Clock::update();
    this->_window.swapBuffer();
    _shadersProcessor->use();
    eventManager->update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

pixel_t WindowActivity::getWidth() const
{
    return _window.getWidth();
}

pixel_t WindowActivity::getHeight() const
{
    return _window.getHeight();
}

void WindowActivity::onResize() {}

WindowActivity::~WindowActivity()
{
    glDeleteVertexArrays(1, &_vertexArrayId);
}
} // namespace ample::window
