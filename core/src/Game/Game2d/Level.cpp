#include "Level.h"
#include "GameException.h"
#include "Debug.h"

namespace ample::game::game2d
{
Level::Level(float layerThikness, float physicsLayerPosition,
             const graphics::Vector2d<float> &frontLayerGravity)
    : _sliceThikness(layerThikness),
      _physicsLayerPosition(physicsLayerPosition),
      _defaultGravity(frontLayerGravity),
      _perspectiveCamera(std::make_shared<graphics::CameraPerspective>(graphics::Vector2d<graphics::pixel_t>{1920, 1080},
                                                                       graphics::Vector2d<graphics::pixel_t>{0, 0},
                                                                       graphics::Vector3d<float>{0.0, 0.0, 0.0},
                                                                       graphics::Vector3d<float>{0.0, 0.0, 1.0},
                                                                       60.0,
                                                                       1920.0 / 1080.0,
                                                                       0.1,
                                                                       1000.0))
{
    createSlice(0);
}

std::shared_ptr<physics::WorldLayer2d> Level::createSlice(const size_t num)
{
    if (_sliceByDistance[num])
    {
        throw GameException{"layer already exists: " + std::to_string(num)};
    }
    _sliceByDistance[num] = std::make_shared<physics::WorldLayer2d>(_defaultGravity,
                                                                    num * _sliceThikness,
                                                                    _sliceThikness,
                                                                    _physicsLayerPosition);
    auto &slice = *_sliceByDistance[num].get();
    slice.addCamera(std::static_pointer_cast<graphics::Camera>(_perspectiveCamera));
    return _sliceByDistance[num];
}

std::shared_ptr<physics::WorldLayer2d> Level::frontSlice() noexcept
{
    return _sliceByDistance[0];
}

std::shared_ptr<physics::WorldLayer2d> Level::numberedSlice(const size_t num)
{
    if (!_sliceByDistance[num])
    {
        throw GameException{"wrong layer number: " + std::to_string(num)};
    }
    return _sliceByDistance[num];
}

std::shared_ptr<graphics::CameraPerspective> Level::camera()
{
    return _perspectiveCamera;
}

std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> &Level::layers() noexcept
{
    return _sliceByDistance;
}
} // namespace ample::game::game2d
