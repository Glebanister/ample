#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window) {}

GameController &Game2d::controller() noexcept
{
    return _gameController;
}
} // namespace ample::game::game2d
