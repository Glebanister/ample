#pragma once

#include <unordered_map>
#include <memory>

#include "LayeredWindowActivity.h"
#include "WorldLayer2d.h"
#include "Vector2d.h"

namespace ample::game::game2d
{
class Game2d : public graphics::LayeredWindowActivity
{
public:
    Game2d(window::Window &window, float sliceThikness, float physicsLayerPosition,
           const graphics::Vector2d<float> &frontSliceGravity = {0.f, -10.f});

    void setSlice(physics::WorldLayer2d &slice, const size_t num);

    physics::WorldLayer2d &frontSlice() noexcept;
    physics::WorldLayer2d &numberedSlice(const size_t num);

private:
    const float _sliceThikness;
    const float _physicsLayerPosition;
    const graphics::Vector2d<float> _defaultGravity;

    std::unordered_map<size_t, physics::WorldLayer2d *> _sliceByDistance;
    physics::WorldLayer2d _frontSlice;
    graphics::Layer _layout;
};
} // namespace ample::game::game2d
