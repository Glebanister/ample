#pragma once

#include "ControlledObject.h"

namespace ample::game
{
class GameController : public ControlledObject
{
public:
    GameController(const std::string &name, const std::string &className);
    GameController(const filing::JsonIO &input);
};
} // namespace ample::game
