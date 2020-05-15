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
    Game2d(const std::string &name,
           const window::pixel_t &x,
           const window::pixel_t &y,
           const window::pixel_t &width,
           const window::pixel_t &height,
           const uint32_t &posFlags,
           const uint32_t &modeFlags,
           const std::filesystem::path &path);

private:
    std::shared_ptr<LevelSwitcher> _levelSwitchingController;
};
} // namespace ample::game::game2d
