#include <string>
#include <exception>
#include <iostream>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <unordered_map>
#include <sstream>

#include "Debug.h"
#include "Exception.h"

namespace ample::exception
{

Exception::Exception(const exId &id, const exType &type, const std::string &message)
    : _id(id), _type(type), _message(message) {}

void Exception::report() const
{
    std::string message = exIdInfo[int(_id)] + ' ' + _message;
    std::cerr << exTypeInfo[int(_type)] << " : " << message << std::endl;
}

const char *Exception::what() const throw()
{
    return _message.c_str();
}

exId Exception::getId() const
{
    return _id;
}

exType Exception::getType() const
{
    return _type;
}

OpenGLException::OpenGLException(const std::string &message)
    : Exception(exId::OPENGL, exType::CRITICAL, message) {}

void OpenGLException::handle(const std::string &message)
{
    auto err = glGetError();
    if (err != GL_NO_ERROR || message.length() != 0)
    {
        throw OpenGLException(message + ' ' + glErrorMessage[err]);
    }
}

SDLException::SDLException(const std::string &message)
    : Exception(exId::SDL, exType::CRITICAL, message) {}

void SDLException::handle(const std::string &message)
{
    if (SDL_GetError() || message.length() != 0)
    {
        throw SDLException(SDL_GetError() + message);
    }
}

void DevILException::handle(const std::string &message, bool throwAnyway)
{
    std::stringstream errorString;
    bool hasError = false;
    ILenum error;
    errorString << message << '\n';
    while ((error = ilGetError()) != IL_NO_ERROR)
    {
        errorString << iluErrorString(error) << '\n';
        hasError = true;
    }
    if (hasError || throwAnyway)
    {
        throw DevILException{std::string(std::istreambuf_iterator<char>(errorString), {})};
    }
}

DevILException::DevILException(const std::string &message)
    : Exception(exId::DEVIL, exType::CRITICAL, message) {}
} // namespace ample::exception
