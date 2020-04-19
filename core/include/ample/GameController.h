#pragma once

#include <memory>

#include "ControlledObject.h"
#include "Game2d.h"

namespace ample::game::game2d
{
class Game2d;
class Level;
} // namespace ample::game::game2d

namespace ample::game
{
class GameController : public ControlledObject, public std::enable_shared_from_this<GameController>
{
public:
    GameController(const std::string &name, const std::string &className, game2d::Game2d &game);
    GameController(const filing::JsonIO &input, game2d::Game2d &game);
    game2d::Game2d &game() noexcept;

private:
    game2d::Game2d &_controlledGame;
};
} // namespace ample::game
