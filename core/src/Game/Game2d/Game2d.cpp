#include <string>

#include "Game2d.h"
#include "GameException.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window)
{
    _layout.addCamera(_orthoCamera);
}

graphics::Layer &Game2d::layout() noexcept
{
    return _layout;
}

graphics::CameraPerspective &Game2d::camera() noexcept
{
    return numberedLevel(_currentLevel).camera();
}

graphics::CameraOrtho &Game2d::view() noexcept
{
    return _orthoCamera;
}

Level &Game2d::currentLevel()
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
        currentLevel().camera().setVisibility(false);
    }
    cleanLayers(); // TODO : cleans all layers, but not their behaviours
    _currentLevel = num;
    currentLevel().camera().setVisibility(true);
    for (auto &[_, layer] : currentLevel().layers())
    {
        addLayer(*layer);
    }
    addLayer(*currentLevel().layers()[0]);
    addLayer(_layout);
}

Level &Game2d::numberedLevel(size_t num)
{
    if (!_levels[num])
    {
        throw GameException{"level does not exists: " + std::to_string(num)};
    }
    return *_levels[num].get();
}
} // namespace ample::game::game2d
