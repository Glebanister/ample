#pragma once

namespace ample::game::game2d
{
template <typename... Args>
Level &Game2d::createLevel(size_t num, Args... args)
{
    if (_levels[num])
    {
        throw GameException{"level with given id is already exists"};
    }
    return *(_levels[num] = std::make_shared<Level>(args...)); // TODO : remove operator=
}
} // namespace ample::game::game2d
