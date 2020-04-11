#include <string>

#include "Game2d.h"
#include "GameException.h"
#include "Utils.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window),
      _layout(std::make_shared<graphics::Layer>()),
      _orthoCamera(std::make_shared<graphics::CameraOrtho>(graphics::Vector2d<graphics::pixel_t>{1920, 1080},
                                                           graphics::Vector2d<graphics::pixel_t>{0, 0},
                                                           graphics::Vector3d<float>{0.0, 0.0, 0.0},
                                                           graphics::Vector3d<float>{0.0, 0.0, 1.0},
                                                           -1920 / 10,
                                                           1920 / 10,
                                                           -1080 / 10,
                                                           1080 / 10,
                                                           0,
                                                           1000))
{
    _layout->addCamera(std::static_pointer_cast<graphics::Camera>(_orthoCamera));
}

std::shared_ptr<graphics::Layer> Game2d::layout() noexcept
{
    return _layout;
}

std::shared_ptr<graphics::CameraPerspective> Game2d::camera() noexcept
{
    return numberedLevel(_currentLevel)->camera();
}

std::shared_ptr<graphics::CameraOrtho> Game2d::view() noexcept
{
    return _orthoCamera;
}

std::shared_ptr<Level> Game2d::currentLevel()
{
    return numberedLevel(_currentLevel);
}

void Game2d::setCurrentLevel(size_t num)
{
    if (!num)
    {
        throw GameException{"level number can not be 0"};
    }
    if (_currentLevel)
    {
        currentLevel()->camera()->setVisibility(false);
    }
    cleanLayers(); // TODO : cleans all layers, but not their behaviours
    _currentLevel = num;
    currentLevel()->camera()->setVisibility(true);
    for (auto &[_, layer] : currentLevel()->layers())
    {
        utils::ignore(_);
        addLayer(layer);
    }
    addLayer(currentLevel()->layers()[0]);
    addLayer(_layout);
}

std::shared_ptr<Level> Game2d::numberedLevel(size_t num)
{
    if (!_levels[num])
    {
        throw GameException{"level does not exists: " + std::to_string(num)};
    }
    return _levels[num];
}
} // namespace ample::game::game2d
