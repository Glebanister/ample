#pragma once

#include <filesystem>

#include "GameException.h"
#include "Level.h"
#include "LevelLoader.h"
#include "StateMachine.h"

namespace ample::game
{
class LevelLoader;
}

namespace ample::game::game2d
{
class Level;
}

namespace ample::game
{
class LevelSwitcher : public StateMachine
{
public:
    LevelSwitcher(const std::filesystem::path &projectPath);
    void save();

private:
    std::string dump() override;
    std::filesystem::path _projectPath;
};
} // namespace ample::game
