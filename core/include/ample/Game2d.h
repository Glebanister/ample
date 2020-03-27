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

    graphics::CameraPerspective &perspectiveCamera() noexcept;
    graphics::CameraOrtho &orthoCamera() noexcept;

    graphics::Layer &layout() noexcept;

    template <typename... Args>
    Level &createLevel(size_t num, Args... args);

private:
    std::unordered_map<size_t, std::shared_ptr<Level>> _levels;
    size_t _currentLevel;
    graphics::Layer _layout;
    graphics::CameraPerspective _perspectiveCamera{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        60.0,
        1920.0 / 1080.0,
        0.1,
        1000.0};
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
