#include "GameController.h"

namespace ample::game
{
GameController::GameController(const std::string &name, const std::string &className, game2d::Game2d &game)
    : ControlledObject(name, className), _controlledGame(game) {}

GameController::GameController(const filing::JsonIO &input, game2d::Game2d &game)
    : ControlledObject(input), _controlledGame(game) {}

game2d::Game2d &GameController::game() noexcept
{
    return _controlledGame;
}
} // namespace ample::game
