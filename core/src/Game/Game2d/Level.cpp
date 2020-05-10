#include <filesystem>

#include "Exception.h"
#include "GameException.h"
#include "JsonIO.h"
#include "Level.h"
#include "Utils.h"

namespace ample::game::game2d
{
Level::Level(const std::string &name,
             float sliceThikness,
             float physicsLayerPosition,
             const graphics::Vector2d<float> &gravity)
    : NamedStoredObject(name, "Level"),
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
      _editingMode(true)
{
}

Level::Level(const std::filesystem::path &path)
    : NamedStoredObject(filing::openJSONfile(path / "settings.json"))
{
    filing::JsonIO cameraSettings(filing::openJSONfile(path / "camera_settings.json"));
    _perspectiveCamera = std::make_shared<graphics::CameraPerspective>(cameraSettings);
    _levelNamespace.addObject(_perspectiveCamera);

    filing::JsonIO settings{filing::openJSONfile(path / "settings.json")};
    _sliceThikness = settings.read<float>("slice_thickness");
    _physicsLayerPosition = settings.read<float>("physics_layer_position");
    ASSERT(0.0f <= _physicsLayerPosition && _physicsLayerPosition <= 1.0f);
    _defaultGravity = settings.read<graphics::Vector2d<float>>("gravity");

    for (const auto &entry : std::filesystem::directory_iterator(path / "scenes"))
    {
        auto newScene = std::make_shared<filing::Scene2d>(filing::openJSONfile(entry.path()), _levelNamespace); // fill level namespace
        _sliceByDistance[newScene->getDistance()] = newScene;
        newScene->setVisibility(false);
        addBehavior(newScene);
    }

    for (const auto &entry : std::filesystem::directory_iterator(path / "state_machines"))
    {
        auto newMachine = std::make_shared<StateMachine>(filing::openJSONfile(entry.path()), _levelNamespace); // use level namespace
        _stateMachines.push_back(newMachine);
        addBehavior(newMachine);
    }

    auto texturesPath = path.parent_path().parent_path() / "textures";
    std::unordered_map<std::string, std::shared_ptr<graphics::Texture>> textureByName;
    for (const auto &entry : std::filesystem::directory_iterator(texturesPath))
    {
        if (entry.path().extension() == ".json")
        {
            std::string textureInfo = utils::readAllFile(entry);
            auto texture = std::make_shared<graphics::Texture>(textureInfo);
            textureByName.emplace(texture->name(), texture);
        }
    }

    auto bindTexture = [&](graphics::GraphicalObject &obj) {
        if (obj.getTextureName().length())
        {
            auto tex = textureByName[obj.getTextureName()];
            if (!tex)
            {
                throw GameException("texture not found: " + obj.getTextureName());
            }
            obj.bindTexture(tex);
        }
    };

    for (const auto &[dist, slice] : _sliceByDistance)
    {
        for (const auto &obj : slice->objects())
        {
            bindTexture(*obj);
            if (obj->className() == "GraphicalObject2d" || obj->className() == "WorldObject2d")
            {
                bindTexture(std::dynamic_pointer_cast<graphics::GraphicalObject2d>(obj)->face());
                bindTexture(std::dynamic_pointer_cast<graphics::GraphicalObject2d>(obj)->side());
            }
        }
    }
}

Namespace &Level::globalNamespace()
{
    return _levelNamespace;
}

void Level::saveAs(const std::filesystem::path &path)
{
    utils::tryCreateDirectory(path);
    std::ofstream cameraFile(path / "camera_settings.json");
    cameraFile << camera()->dump();
    cameraFile.close();

    filing::JsonIO settingsJson = NamedStoredObject::dump();
    settingsJson.write<float>("slice_thickness", _sliceThikness);
    settingsJson.write<float>("physics_layer_position", _physicsLayerPosition);
    settingsJson.write<graphics::Vector2d<float>>("gravity", _defaultGravity);
    std::ofstream settingsFile(path / "settings.json");
    settingsFile << settingsJson.getJSONstring();
    settingsFile.close();

    utils::tryCreateDirectory(path / "scenes");
    for (const auto &[dist, slice] : _sliceByDistance)
    {
        std::string sliceData = slice->dump();
        std::ofstream sliceFile(path / "scenes" / (slice->name() + ".json"));
        sliceFile << sliceData;
    }

    utils::tryCreateDirectory(path / "state_machines");
    for (const auto &machine : _stateMachines)
    {
        std::string smdata = machine->dump();
        std::ofstream machineFile(path / "state_machines" / (machine->name() + ".json"));
        machineFile << smdata;
    }

    auto texturesPath = path.parent_path().parent_path() / "textures";
    utils::tryCreateDirectory(texturesPath);

    auto saveTexture = [&](graphics::GraphicalObject &obj) {
        if (obj.texture())
        {
            obj.texture()->setPath(texturesPath);
            auto texInfoPath = texturesPath / (obj.texture()->name() + ".json");
            if (std::filesystem::exists(texInfoPath))
            {
                return;
            }
            std::ofstream textureInfo(texInfoPath);
            textureInfo << obj.texture()->dump();
        }
    };

    for (const auto &[dist, slice] : _sliceByDistance)
    {
        for (const auto &obj : slice->objects())
        {
            saveTexture(*std::dynamic_pointer_cast<graphics::GraphicalObject2d>(obj));
            if (obj->className() == "GraphicalObject2d" || obj->className() == "WorldObject2d")
            {
                saveTexture(std::dynamic_pointer_cast<graphics::GraphicalObject2d>(obj)->face());
                saveTexture(std::dynamic_pointer_cast<graphics::GraphicalObject2d>(obj)->side());
            }
        }
    }
}

void Level::onActive()
{
    Behavior::onActive();
    if (_editingMode)
    {
        return;
    }
    _perspectiveCamera->look();
    for (auto &[_, slice] : _sliceByDistance)
    {
        utils::ignore(_);
        for (const auto &obj : slice->objects())
        {
            obj->draw();
        }
    }
}

void Level::setGravity(const graphics::Vector2d<float> &gravity) noexcept
{
    _defaultGravity = gravity;
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
    _sliceByDistance[num]->setVisibility(false);
    addBehavior(_sliceByDistance[num]);
    return _sliceByDistance[num];
}

std::shared_ptr<StateMachine> Level::createStateMachine(const std::string &name)
{
    _stateMachines.emplace_back(std::make_shared<StateMachine>(name));
    return _stateMachines.back();
}

std::vector<std::shared_ptr<StateMachine>> Level::stateMachines() noexcept
{
    return _stateMachines;
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
