#include "GLContext.h"
#include "Exception.h"
#include "Debug.h"
#include "OpenGLEnvironment.h"

namespace ample::os
{
GLContext::GLContext(SDL_Window *_winPtr)
{
    _context = SDL_GL_CreateContext(_winPtr);

    if (!_context)
    {
        exception::OpenGLException::handle();
        exception::SDLException::handle();
        throw exception::Exception(exception::exId::OPENGL_INIT,
                                   exception::exType::CRITICAL,
                                   "unable to create gl context");
    }
    os::environment::OpenGLEnvironment::instance();
}

SDL_GLContext *GLContext::pointer() noexcept
{
    return &_context;
}

GLContext::~GLContext()
{
    SDL_GL_DeleteContext(_context);
}
} // namespace ample::os
