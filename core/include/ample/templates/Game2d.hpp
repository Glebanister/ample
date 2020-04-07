#pragma once

namespace ample::game::game2d
{
template <typename... Args>
std::shared_ptr<Level> Game2d::createLevel(size_t num, Args... args)
{
    if (_levels[num])
    {
        throw GameException{"level with given id is already exists"};
    }
    if (!num)
    {
        throw GameException{"level can not have 0 as id"};
    }
    auto level = _levels[num] = std::make_shared<Level>(args...);
    level->camera()->setVisibility(false);
    return level; // TODO : remove operator=
}
} // namespace ample::game::game2d
