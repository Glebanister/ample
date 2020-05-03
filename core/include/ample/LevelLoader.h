#pragma once

#include "LevelSwitcher.h"
#include "StateMachine.h"
#include "Level.h"

namespace ample::game
{
class LevelSwitcher;
}

namespace ample::game::game2d
{
class Level;
}

namespace ample::game
{
class LevelLoader : public StateMachine::State
{
public:
    LevelLoader(const std::filesystem::path &levelPath,
                LevelSwitcher &machine);

    void onStart();
    void onActive();
    void onStop();
    game2d::Level &level() noexcept;

private:
    const std::filesystem::path _levelPath;
    std::unique_ptr<game2d::Level> _level;
};
} // namespace ample::game
