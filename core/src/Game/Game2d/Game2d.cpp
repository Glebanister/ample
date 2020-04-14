#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window),
      _gameController(std::make_shared<GameController>("game_controller", "GameController"))
{
}

GameController &Game2d::controller() noexcept
{
    return *_gameController;
}

std::shared_ptr<GameController> Game2d::controllerPointer() const noexcept
{
    return _gameController;
}
} // namespace ample::game::game2d
