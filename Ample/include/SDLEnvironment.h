#pragma once

namespace ample::os::environment
{
class SDLEnvironment final
{
public:
    SDLEnvironment &instance();

private:
    SDLEnvironment();
};
} // namespace ample::os::environment
