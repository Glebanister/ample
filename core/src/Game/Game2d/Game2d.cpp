#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window),
      _gameController(std::make_shared<GameController>("game_controller", "GameController", *this))
{
    addBehavior(_gameController);
}

GameController &Game2d::controller() noexcept
{
    return *_gameController;
}

std::shared_ptr<GameController> Game2d::controllerPointer() const noexcept
{
    return _gameController;
}

std::shared_ptr<game2d::Level> Game2d::createLevel(const std::string &name,
                                                   const float sliceThickness,
                                                   const float physicsLayerPosition,
                                                   const graphics::Vector2d<float> &gravity)
{
    return std::make_shared<game2d::Level>(name,
                                           _gameController,
                                           sliceThickness,
                                           physicsLayerPosition,
                                           gravity);
}

void Game2d::setCurrentLevel(std::shared_ptr<Level> level)
{
    _gameController->stateMachine()->setStartState(level);
}

std::shared_ptr<Level> Game2d::currentLevel() const noexcept
{
    return std::static_pointer_cast<Level>(_gameController->stateMachine()->getCurrentState());
}
} // namespace ample::game::game2d
