#include "GameController.h"

namespace ample::game
{
GameController::GameController(const std::string &name, const std::string &className)
    : ControlledObject(name, className) {}

GameController::GameController(const filing::JsonIO &input)
    : ControlledObject(input) {}
} // namespace ample::game
