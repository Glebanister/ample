#include <filesystem>

#include "Exception.h"
#include "GameEnvironment.h"
#include "GameException.h"
#include "JsonIO.h"
#include "Level.h"
#include "Utils.h"

namespace ample::game::game2d
{
Level::Level(const std::filesystem::path &path,
             StateMachine &controller)
    : State(filing::JsonIO(filing::openJSONfile(path / "settings.json")).read<std::string>("name"), controller),
      _path(path)
{
    filing::JsonIO settings{filing::openJSONfile(path / "settings.json")};
    _sliceThikness = settings.read<float>("slice_thickness");
    _physicsLayerPosition = settings.read<float>("physics_layer_poistion");
    ASSERT(0.0f <= _physicsLayerPosition && _physicsLayerPosition <= 1.0f);
    _defaultGravity = settings.read<graphics::Vector2d<float>>("gravity");
    for (const auto &entry : std::filesystem::directory_iterator(path / "scenes"))
    {
        // TODO: use std::unordered_map::emplace
        auto newScene = std::make_shared<filing::Scene2d>(filing::openJSONfile(entry.path()));
        _sliceByDistance[newScene->getDistance()] = newScene;
    }
}

void tryCreateDirectory(const std::filesystem::path &path)
{
    if (!(std::filesystem::exists(path) && std::filesystem::is_directory(path)))
    {
        if (!std::filesystem::create_directory(path))
        {
            throw exception::Exception(exception::exId::UNSPECIFIED,
                                       exception::exType::CASUAL,
                                       "can not create directory: " + std::string(path));
        }
    }
}

void Level::save()
{
    tryCreateDirectory(_path);
    tryCreateDirectory(_path / "scenes");

    std::ofstream settingsFile(_path / "settings.json");
    filing::JsonIO settingsJson;
    settingsJson.write<float>("slice_thickness", _sliceThikness);
    settingsJson.write<float>("physics_layer_position", _physicsLayerPosition);
    settingsJson.write<graphics::Vector2d<float>>("gravity", _defaultGravity);
    settingsFile << settingsJson.getJSONstring();
    for (const auto &[dist, slice] : _sliceByDistance)
    {
        std::ofstream sliceFile(_path / "scenes" / (slice->name() + ".json"));
        sliceFile << slice->dump().getJSONstring();
    }
}

Level::Level(const std::string &name,
             StateMachine &controller,
             float sliceThikness,
             float physicsLayerPosition,
             const graphics::Vector2d<float> &gravity,
             const std::filesystem::path &destPath)
    : State(controller, name),
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
                                                                       1000.0)),
      _editingMode(true),
      _path(destPath)
{
    createSlice(0, "front_slice");
}

void Level::onActive()
{
    State::onActive();
    if (_editingMode)
    {
        return;
    }
    _perspectiveCamera->look();
    for (auto &[_, slice] : _sliceByDistance)
    {
        for (const auto &obj : slice->objects())
        {
            obj->draw();
        }
    }
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
    slice.setVisibility(false);
    addBehavior(_sliceByDistance[num]);
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
} // namespace ample::game::game2d
