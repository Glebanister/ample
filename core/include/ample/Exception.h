#pragma once

#include <GL/gl.h>
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>

namespace ample::exception
{
enum class exId : size_t
{
    NO,
    UNSPECIFIED,
    FILE_READ,
    FILE_WRITE,
    NULLPTR,
    LOGIC,
    WINDOW_OPEN,
    SDL_INIT,
    OPENGL_INIT,
    SDL_DOUBLE_INIT,
    SDL_NOT_READY,
    OPENGL_NOT_FIT,
    OPENGL_SHADER,
    WINDOW_NOT_READY,
    OPENGL,
    SDL,
    DEVIL,
    GAME,
};

static std::string exIdInfo[] = {
    "success",
    "error occured",
    "can't read file",
    "can't write to file",
    "dereferencing nullptr",
    "logic error",
    "can't create window",
    "can't init SDL2",
    "can't init OpenGL",
    "SDL double initialization",
    "can't use SDL2: not initializated",
    "OpenGL context can't fit to the window",
    "OpenGL can't load shader",
    "can't use window: not ready yet",
    "OpenGL error occured",
    "SDL error occured",
    "DevIL error occured",
    "game error occured",
};

enum class exType : size_t
{
    CRITICAL,
    CASUAL,
};

static std::string exTypeInfo[] = {
    "CRITICAL",
    "EXCEPTION",
};

class Exception : public std::exception
{
public:
    explicit Exception(const exId &id,
                       const exType &type,
                       const std::string &message = "");

    const char *what() const throw();

    void report() const;

    exId getId() const;

    exType getType() const;

private:
    exId _id = exId::UNSPECIFIED;
    exType _type = exType::CRITICAL;
    std::string _message = "";
};

static std::unordered_map<int, std::string> glErrorMessage{
    {GL_NO_ERROR, "GL_NO_ERROR No error has been recorded."},
    {GL_INVALID_ENUM, "GL_INVALID_ENUM An unacceptable value is specified for an enumerated argument."},
    {GL_INVALID_VALUE, "GL_INVALID_VALUE A numeric argument is out of range."},
    {GL_INVALID_OPERATION, "GL_INVALID_OPERATION The specified operation is not allowed in the current state."},
    {GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION The framebuffer object is not complete."},
    {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY There is not enough memory left to execute the command."},
    {GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW An attempt has been made to perform an operation that would cause an internal stack to underflow."},
    {GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW An attempt has been made to perform an operation that would cause an internal stack to overflow."},
};

class OpenGLException : public Exception
{
public:
    static void handle(const std::string &message = "");

private:
    explicit OpenGLException(const std::string &message = "");
};

class SDLException : public Exception
{
public:
    static void handle(const std::string &message = "");

private:
    explicit SDLException(const std::string &message = "");
};

class DevILException : public Exception
{
public:
    static void handle(const std::string &message = "", bool throwAnyway = false);
    explicit DevILException(const std::string &message = "");
};
} // namespace ample::exception
