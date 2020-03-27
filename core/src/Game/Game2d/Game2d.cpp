#include <string>

#include "Game2d.h"
#include "GameException.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window)
    : graphics::LayeredWindowActivity(window)
{
    _perspectiveCamera.setVisibility(true);
    _orthoCamera.setVisibility(true);
    _layout.addCamera(_orthoCamera);
}

graphics::Layer &Game2d::layout() noexcept
{
    return _layout;
}

graphics::CameraPerspective &Game2d::perspectiveCamera() noexcept
{
    return _perspectiveCamera;
}

graphics::CameraOrtho &Game2d::orthoCamera() noexcept
{
    return _orthoCamera;
}
} // namespace ample::game::game2d
