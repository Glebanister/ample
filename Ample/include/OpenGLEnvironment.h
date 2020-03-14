#pragma once

namespace ample::os::environment
{
class OpenGLEnvironment final
{
public:
    OpenGLEnvironment &instance();

private:
    OpenGLEnvironment();
};
} // namespace ample::os::environment
