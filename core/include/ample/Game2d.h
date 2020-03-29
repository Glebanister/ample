#pragma once

#include <unordered_map>
#include <memory>

#include "LayeredWindowActivity.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "GameException.h"
#include "CameraPerspective.h"
#include "CameraOrtho.h"
#include "Debug.h"
#include "Level.h"

namespace ample::game::game2d
{
class Game2d : public graphics::LayeredWindowActivity
{
public:
    Game2d(window::Window &window);

    graphics::CameraPerspective &camera() noexcept;
    graphics::CameraOrtho &view() noexcept;

    graphics::Layer &layout() noexcept;

    template <typename... Args>
    Level &createLevel(size_t num, Args... args);
    Level &numberedLevel(size_t num);
    Level &currentLevel();

    void setCurrentLevel(size_t levelNum);

private:
    std::unordered_map<size_t, std::shared_ptr<Level>> _levels;
    size_t _currentLevel = 0;
    graphics::Layer _layout;
    graphics::CameraOrtho _orthoCamera{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        -1920 / 10,
        1920 / 10,
        -1080 / 10,
        1080 / 10,
        0,
        1000};
};
} // namespace ample::game::game2d

#include "templates/Game2d.hpp"
