#include "GameException.h"

namespace ample::game
{
GameException::GameException(const std::string &message)
    : Exception(ample::exception::exId::GAME,
                ample::exception::exType::CRITICAL,
                message)
{
}
} // namespace ample::game
