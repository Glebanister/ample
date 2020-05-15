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
      _levelSwitchingController(std::make_shared<LevelSwitcher>(path)),
      _skybox("skybox", "GraphicalObject")
{
    addBehavior(_levelSwitchingController);

    graphics::Vector3d<float> A = {-550, -550, -550};
    graphics::Vector3d<float> B = {550, -550, -550};
    graphics::Vector3d<float> C = {550, 550, -550};
    graphics::Vector3d<float> D = {-550, 550, -550};
    graphics::Vector3d<float> A1 = {-550, -550, 550};
    graphics::Vector3d<float> B1 = {550, -550, 550};
    graphics::Vector3d<float> C1 = {550, 550, 550};
    graphics::Vector3d<float> D1 = {-550, 550, 550};

    std::vector<graphics::Vector3d<float>> coords{
        A, B, C,
        A, C, D,
        D, C, C1,
        D, C1, D1,
        D, D1, A1,
        D, A1, A,
        B, A, A1,
        B, A1, B1,
        C, C1, B1,
        C, B1, B,
        D1, C1, A1,
        C1, B1, A1};
    std::vector<graphics::Vector2d<float>> uv{
        {0.f / 4.f, 1.f / 3.f}, {0.f / 4.f, 2.f / 3.f}, {1.f / 4.f, 2.f / 3.f}, {0.f / 4.f, 1.f / 3.f}, {1.f / 4.f, 2.f / 3.f}, {1.f / 4.f, 1.f / 3.f}, {1.f / 4.f, 1.f / 3.f}, {1.f / 4.f, 2.f / 3.f}, {2.f / 4.f, 2.f / 3.f}, {1.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 2.f / 3.f}, {2.f / 4.f, 1.f / 3.f}, {1.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 0.f / 3.f}, {1.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 0.f / 3.f}, {1.f / 4.f, 0.f / 3.f}, {1.f / 4.f, 4.f / 3.f}, {1.f / 4.f, 3.f / 3.f}, {2.f / 4.f, 3.f / 3.f}, {1.f / 4.f, 4.f / 3.f}, {2.f / 4.f, 3.f / 3.f}, {2.f / 4.f, 4.f / 3.f}, {1.f / 4.f, 2.f / 3.f}, {2.f / 4.f, 2.f / 3.f}, {2.f / 4.f, 4.f / 3.f}, {1.f / 4.f, 2.f / 3.f}, {2.f / 4.f, 4.f / 3.f}, {1.f / 4.f, 4.f / 3.f}, {2.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 2.f / 3.f}, {4.f / 4.f, 1.f / 3.f}, {2.f / 4.f, 2.f / 3.f}, {4.f / 4.f, 2.f / 3.f}, {4.f / 4.f, 1.f / 3.f}};

    std::vector<graphics::Vector3d<float>> norm{
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, -1, 0},
        {0, -1, 0},
        {0, -1, 0},
        {0, -1, 0},
        {0, -1, 0},
        {0, -1, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {-1, 0, 0},
        {-1, 0, 0},
        {-1, 0, 0},
        {-1, 0, 0},
        {-1, 0, 0},
        {-1, 0, 0},
        {0, 0, -1},
        {0, 0, -1},
        {0, 0, -1},
        {0, 0, -1},
        {0, 0, -1},
        {0, 0, -1},
    };

    _skybox.bindTexture(std::make_shared<graphics::Texture>(
        graphics::TextureRaw(
            "../../../Desktop/skybox.jpg",
            "skybox_texture",
            {0, 0},
            {0, 0},
            {1, 1},
            graphics::channelMode::RGBA,
            graphics::texturePlayback::NORMAL)));
    auto skyboxArray = std::make_shared<graphics::VertexArray>(coords, uv, norm);
    _skybox.bindVertexArray(skyboxArray);
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
    _skybox.draw();
    _skybox.setTranslate({_camera->getX(), _camera->getY(), _camera->getZ()});
}
} // namespace ample::game::game2d
