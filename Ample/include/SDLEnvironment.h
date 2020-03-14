#pragma once

namespace ample::os::environment
{
class SDLEnvironment final
{
public:
    static SDLEnvironment &instance();

private:
    SDLEnvironment();
    ~SDLEnvironment();
};
} // namespace ample::os::environment
