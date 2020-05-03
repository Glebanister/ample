#include "LevelLoader.h"

namespace ample::game
{
LevelLoader::LevelLoader(const std::filesystem::path &levelPath,
                         LevelSwitcher &machine,
                         const game::Namespace &globalNamespace) // TODO: immediate mode (without reset)
    : State(filing::openJSONfile(levelPath / "level_state.json"),
            machine,
            globalNamespace),
      _levelPath(levelPath)
{
}

void LevelLoader::onStart()
{
    Behavior::onStart();
    _level = std::make_unique<game2d::Level>(_levelPath);
}

void LevelLoader::onActive()
{
    Behavior::onActive();
    _level->onActive();
}

void LevelLoader::onStop()
{
    Behavior::onStop();
    _level.reset();
}
} // namespace ample::game
