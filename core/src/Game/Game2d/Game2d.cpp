#include <string>
#include <tuple>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

struct node
{
    ample::graphics::Vector3d<float> c;
    ample::graphics::Vector2d<float> u;
    ample::graphics::Vector3d<float> n;
};

namespace ample::game::game2d
{
Game2d::Game2d(const std::string &name,
               const window::pixel_t &x,
               const window::pixel_t &y,
               const window::pixel_t &width,
               const window::pixel_t &height,
               const uint32_t &posFlags,
               const uint32_t &modeFlags,
               const std::filesystem::path &path)
    : graphics::LayeredWindowActivity(name, x, y, width, height, posFlags, modeFlags),
      _levelSwitchingController(std::make_shared<LevelSwitcher>(path))
{
    addBehavior(_levelSwitchingController);
}

// stub for camera moving. TODO: implement camera actions
void Game2d::onActive()
{
    graphics::LayeredWindowActivity::onActive();
}
} // namespace ample::game::game2d
