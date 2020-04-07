#include "GameEnvironment.h"

namespace ample::game
{

GameEnvironment::GameEnvironment(const std::string &projectAbsolutePath)
    : _projectAbsolutePath(projectAbsolutePath) {}

const std::string &GameEnvironment::projectAbsolutePath() const
{
    return _projectAbsolutePath;
}
} // namespace ample::game
