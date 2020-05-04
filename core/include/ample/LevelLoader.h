#pragma once

#include "Level.h"
#include "LevelSwitcher.h"
#include "StateMachine.h"

namespace ample::game
{
class LevelSwitcher;
}

namespace ample::game::game2d
{
class Level;
}

// TODO: immediate mode (without reset)

namespace ample::game
{
class LevelLoader : public StateMachine::State
{
public:
    LevelLoader(const std::filesystem::path &projectPath,
                const std::string &name,
                LevelSwitcher &machine);
    LevelLoader(const std::filesystem::path &existingLevelPath,
                LevelSwitcher &machine);

    void onStart();
    void onActive();
    void onStop();

    std::string levelName() const noexcept;

private:
    const std::filesystem::path _levelPath;
    std::unique_ptr<game2d::Level> _level;
    const std::string _levelName;
};
} // namespace ample::game
