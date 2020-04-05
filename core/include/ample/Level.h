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

    std::shared_ptr<physics::WorldLayer2d> createSlice(const size_t num);
    std::shared_ptr<physics::WorldLayer2d> frontSlice() noexcept;
    std::shared_ptr<physics::WorldLayer2d> numberedSlice(const size_t num);

    std::shared_ptr<graphics::CameraPerspective> camera();

    std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> &layers() noexcept;

private:
    const float _sliceThikness;
    const float _physicsLayerPosition;
    const graphics::Vector2d<float> _defaultGravity;
    std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> _sliceByDistance;
    std::shared_ptr<graphics::CameraPerspective> _perspectiveCamera;
};
} // namespace ample::game::game2d
