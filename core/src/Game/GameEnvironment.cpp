#include "GameEnvironment.h"

namespace ample::game
{
std::filesystem::path &GameEnvironment::projectAbsolutePath()
{
    return _projectAbsolutePath;
}
} // namespace ample::game
