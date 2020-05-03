#include "LevelLoader.h"

namespace ample::game
{
LevelLoader::LevelLoader(const std::filesystem::path &levelPath,
                         LevelSwitcher &machine) // TODO: immediate mode (without reset)
    : State(filing::openJSONfile(levelPath / "level_state.json"),
            machine),
      _levelPath(levelPath)
{
}

game2d::Level &LevelLoader::level() noexcept
{
    return *_level;
}

void LevelLoader::onStart()
{
    Behavior::onStart();
    _level = std::make_unique<game2d::Level>(_levelPath);
    fillActionsNamespace(_level->globalNamespace());
    fillTransitionsNamespace(_level->globalNamespace());
}

void LevelLoader::onActive()
{
    Behavior::onActive();
    _level->onActive();
}

void LevelLoader::onStop()
{
    Behavior::onStop();
    for (auto &transition : transitions())
    {
        transition->getNamespace().clear();
    }
    for (auto &action : getOnStartActions())
    {
        action->getNamespace().clear();
    }
    for (auto &action : getOnActiveActions())
    {
        action->getNamespace().clear();
    }
    for (auto &action : getOnStopActions())
    {
        action->getNamespace().clear();
    }
    _level.reset();
}
} // namespace ample::game
