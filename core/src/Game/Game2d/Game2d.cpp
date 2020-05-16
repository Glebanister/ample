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

    auto curLevel = std::dynamic_pointer_cast<LevelLoader>(_levelSwitchingController->getCurrentState());
    auto _camera = curLevel->level().camera();
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::KEY_d))
    {
        _camera->moveRight(1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::KEY_a))
    {
        _camera->moveRight(-1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::ARROW_UP))
    {
        _camera->rotateUp(1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        _camera->rotateUp(-1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::KEY_w))
    {
        _camera->moveForward(1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::KEY_s))
    {
        _camera->moveForward(-1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        _camera->rotateRight(1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        _camera->rotateRight(-1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::COMMA))
    {
        _camera->rotateForward(-1);
    }
    if (control::EventManager::instance().keyboard().isKeyDown(ample::control::keysym::PERIOD))
    {
        _camera->rotateForward(1);
    }
}
} // namespace ample::game::game2d
