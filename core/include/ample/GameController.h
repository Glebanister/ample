#pragma once

#include <memory>

#include "ControlledObject.h"

namespace ample::game
{
class GameController : public ControlledObject, public std::enable_shared_from_this<GameController>
{
public:
    GameController(const std::string &name, const std::string &className);
    GameController(const filing::JsonIO &input);
};
} // namespace ample::game
