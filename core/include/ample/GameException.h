#pragma once

#include <string>

#include "Exception.h"

namespace ample::game
{
class GameException : public exception::Exception
{
public:
    GameException(const std::string &message);
};
} // namespace ample::game
