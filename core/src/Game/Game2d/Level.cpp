#include <filesystem>

#include "Level.h"
#include "JsonIO.h"
#include "Exception.h"
#include "Utils.h"
#include "GameEnvironment.h"
#include "GameException.h"

namespace ample::game::game2d
{
Level::Level(const std::string &name, std::shared_ptr<GameController> controller)
    : ObjectState(name, controller)
{
    filing::JsonIO settings{filing::openJSONfile(GameEnvironment::instance().projectAbsolutePath() / name / "settings.json")};
    _sliceThikness = settings.read<float>("slice_thickness");
    _physicsLayerPosition = settings.read<float>("physics_layer_poistion");
    ASSERT(0.0f <= _physicsLayerPosition && _physicsLayerPosition <= 1.0f);
    _defaultGravity = settings.read<graphics::Vector2d<float>>("gravity");
    for (const auto &entry : std::filesystem::directory_iterator(GameEnvironment::instance().projectAbsolutePath() / name / "scenes"))
    {
        // TODO: use std::unordered_map::emplace
        auto newScene = std::make_shared<filing::Scene2d>(filing::openJSONfile(entry.path()));
        _sliceByDistance[newScene->getDistance()] = newScene;
    }
}

Level::Level(const std::string &name,
             std::shared_ptr<GameController> controller,
             float sliceThikness,
             float physicsLayerPosition,
             const graphics::Vector2d<float> &gravity)
    : ObjectState(name, controller),
      _sliceThikness(sliceThikness),
      _physicsLayerPosition(physicsLayerPosition),
      _defaultGravity(gravity),
      _perspectiveCamera(std::make_shared<graphics::CameraPerspective>(name + ".perspective_level_camera",
                                                                       graphics::Vector2d<graphics::pixel_t>{1920, 1080},
                                                                       graphics::Vector2d<graphics::pixel_t>{0, 0},
                                                                       graphics::Vector3d<float>{0.0, 0.0, 0.0},
                                                                       graphics::Vector3d<float>{0.0, 0.0, 1.0},
                                                                       60.0,
                                                                       1920.0 / 1080.0,
                                                                       0.1,
                                                                       1000.0))
{
    createSlice(0, "front_slice");
}

std::shared_ptr<filing::Scene2d> Level::createSlice(const size_t num, const std::string &name)
{
    if (_sliceByDistance[num])
    {
        throw GameException{"layer already exists: " + std::to_string(num)};
    }
    _sliceByDistance[num] = std::make_shared<filing::Scene2d>(name,
                                                              _defaultGravity,
                                                              num * _sliceThikness,
                                                              _sliceThikness,
                                                              _physicsLayerPosition);
    auto &slice = *_sliceByDistance[num].get();
    slice.addCamera(std::static_pointer_cast<graphics::Camera>(_perspectiveCamera));
    return _sliceByDistance[num];
}

std::shared_ptr<filing::Scene2d> Level::frontSlice() noexcept
{
    return _sliceByDistance[0];
}

std::shared_ptr<filing::Scene2d> Level::numberedSlice(const size_t num)
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

std::unordered_map<size_t, std::shared_ptr<filing::Scene2d>> &Level::layers() noexcept
{
    return _sliceByDistance;
}

void Level::addGlobalObject(std::shared_ptr<graphics::GraphicalObject> obj)
{
    for (auto &[_, slice] : _sliceByDistance)
    {
        utils::ignore(_);
        slice->addObject(obj);
    }
}

void Level::removeGlobalObject(std::shared_ptr<graphics::GraphicalObject> obj)
{
    for (auto &[_, slice] : _sliceByDistance)
    {
        utils::ignore(_);
        slice->removeObject(obj);
    }
}
} // namespace ample::game::game2d
