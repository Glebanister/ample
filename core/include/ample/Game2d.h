#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "LayeredWindowActivity.h"
#include "Level.h"
#include "LevelSwitcher.h"

/*
*/

namespace ample::game::game2d
{
class Game2d : public graphics::LayeredWindowActivity
{
public:
    Game2d(window::Window &window,
           const std::filesystem::path &path);

private:
    std::shared_ptr<LevelSwitcher> _levelSwitchingController;
};
} // namespace ample::game::game2d
