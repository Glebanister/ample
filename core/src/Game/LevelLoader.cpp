#include "LevelLoader.h"

namespace ample::game
{
LevelLoader::LevelLoader(const std::filesystem::path &levelPath,
                         LevelSwitcher &machine)
    : State(filing::openJSONfile(levelPath / "level_state.json"),
            machine),
      _levelPath(levelPath),
      _levelName(filing::JsonIO(filing::openJSONfile(levelPath / "level_state.json")).read<std::string>("name"))
{
}

LevelLoader::LevelLoader(const std::filesystem::path &projectPath,
                         const std::string &name,
                         LevelSwitcher &machine)
    : State(machine, name),
      _levelPath(projectPath / name),
      _levelName(name)
{
}

std::string LevelLoader::levelName() const noexcept
{
    return _levelName;
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
    ASSERT(_level);
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
