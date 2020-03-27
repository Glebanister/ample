#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "Camera.h"
#include "CameraPerspective.h"

namespace ample::game::game2d
{
class Level
{
public:
    Level(float sliceThikness,
          float physicsLayerPosition,
          const graphics::Vector2d<float> &gravity = {0.f, -10.f});

    Level(const std::string &levelPath);

    physics::WorldLayer2d &createSlice(const size_t num);
    physics::WorldLayer2d &frontSlice() noexcept;
    physics::WorldLayer2d &numberedSlice(const size_t num);

    graphics::CameraPerspective &camera();

    std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> &layers() noexcept;

private:
    const float _sliceThikness;
    const float _physicsLayerPosition;
    const graphics::Vector2d<float> _defaultGravity;
    std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> _sliceByDistance;
    graphics::CameraPerspective _perspectiveCamera{
        {1920, 1080},
        {0, 0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        60.0,
        1920.0 / 1080.0,
        0.1,
        1000.0};
};
} // namespace ample::game::game2d
