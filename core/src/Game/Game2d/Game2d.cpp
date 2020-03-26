#include <string>

#include "Game2d.h"
#include "GameException.h"

namespace ample::game::game2d
{
Game2d::Game2d(window::Window &window, float layerThikness, float physicsLayerPosition,
               const graphics::Vector2d<float> &frontLayerGravity)
    : graphics::LayeredWindowActivity(window),
      _sliceThikness(layerThikness),
      _physicsLayerPosition(physicsLayerPosition),
      _frontSlice(frontLayerGravity),
      _defaultGravity(frontLayerGravity)
{
    addLayer(_frontSlice);
    _sliceByDistance[0] = &_frontSlice;
}

void Game2d::setSlice(physics::WorldLayer2d &slice, const size_t num)
{
    _sliceByDistance[num] = &slice;
}

physics::WorldLayer2d &Game2d::frontSlice() noexcept
{
    return _frontSlice;
}

physics::WorldLayer2d &Game2d::numberedSlice(const size_t num)
{
    if (!_sliceByDistance[num])
    {
        throw GameException{"wrong layer number: " + std::to_string(num)};
    }
    return *_sliceByDistance[num];
}
} // namespace ample::game::game2d
