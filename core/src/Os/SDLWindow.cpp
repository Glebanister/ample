#include "SDLWindow.h"
#include "Exception.h"
#include "Debug.h"
#include "SDLEnvironment.h"

namespace ample::window
{
SDLWindow::SDLWindow(const std::string &title,
                     int x,
                     int y,
                     int w,
                     int h,
                     uint32_t posFlags,
                     uint32_t modeFlags)
{
    os::environment::SDLEnvironment::instance();
    if (posFlags & winpos::CENTERED_X)
    {
        x = SDL_WINDOWPOS_CENTERED;
    }
    if (posFlags & winpos::CENTERED_Y)
    {
        y = SDL_WINDOWPOS_CENTERED;
    }
    if (posFlags & winpos::UNDEFINED_POS)
    {
        x = SDL_WINDOWPOS_UNDEFINED;
        y = SDL_WINDOWPOS_UNDEFINED;
    }
    _winPtr = SDL_CreateWindow(title.c_str(), x, y, w, h, modeFlags | SDL_WINDOW_OPENGL);
    if (!_winPtr)
    {
        exception::SDLException::handle();
        throw exception::Exception(exception::exId::WINDOW_OPEN,
                                   exception::exType::CRITICAL,
                                   "unable to create window");
    }
}

SDL_Window *SDLWindow::pointer() noexcept
{
    return _winPtr;
}

SDLWindow::~SDLWindow()
{
    SDL_DestroyWindow(_winPtr);
}
} // namespace ample::window
