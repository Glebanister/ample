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

    std::shared_ptr<graphics::CameraPerspective> camera() noexcept;
    std::shared_ptr<graphics::CameraOrtho> view() noexcept;

    std::shared_ptr<graphics::Layer> layout() noexcept;

    template <typename... Args>
    std::shared_ptr<Level> createLevel(size_t num, Args... args);
    std::shared_ptr<Level> numberedLevel(size_t num);
    std::shared_ptr<Level> currentLevel();

    void setCurrentLevel(size_t levelNum);

private:
    std::unordered_map<size_t, std::shared_ptr<Level>> _levels;
    size_t _currentLevel = 0;
    std::shared_ptr<graphics::Layer> _layout;
    std::shared_ptr<graphics::CameraOrtho> _orthoCamera;
};
} // namespace ample::game::game2d

#include "templates/Game2d.hpp"
