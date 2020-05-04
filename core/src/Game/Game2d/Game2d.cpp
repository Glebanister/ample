#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window,
               const std::filesystem::path &path)
    : graphics::LayeredWindowActivity(window),
      _levelSwitchingController(std::make_shared<LevelSwitcher>(path))
{
    addBehavior(_levelSwitchingController);
}
} // namespace ample::game::game2d
