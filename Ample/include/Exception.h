#pragma once

#include <string>
#include <exception>
#include <iostream>

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
} // namespace ample::exception
