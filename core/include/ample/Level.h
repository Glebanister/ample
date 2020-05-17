#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "Camera.h"
#include "CameraPerspective.h"
#include "LevelSwitcher.h"
#include "Scene2d.h"
#include "StateMachine.h"
#include "StoredObject.h"
#include "Vector2d.h"
#include "WorldLayer2d.h"
#include "LightSource.h"

/*
class Level

Directory structure
.
├── settings.json                   -- current level settings
├── scenes                          -- all 'slices' of level: foreground, backgrounds
│   └── <...>.json
├── state_machines                  -- all state machines of current level
│   └── <...>.json
├── camera_settings.json            -- level camera setup
└── level_state.json                -- level camera setup
*/

namespace ample::game
{
class LevelSwitcher;
}

namespace ample::game::game2d
{
class Level : public activity::Behavior, public filing::NamedStoredObject
{
public:
    Level(const std::filesystem::path &path);
    void saveAs(const std::filesystem::path &path);

    Level(const std::string &name,
          float sliceThikness,
          float physicsLayerPosition,
          const graphics::Vector2d<float> &gravity);

    void onActive() override;

    std::shared_ptr<filing::Scene2d> createSlice(const size_t num, const std::string &name);
    std::shared_ptr<StateMachine> createStateMachine(const std::string &name);
    std::shared_ptr<filing::Scene2d> numberedSlice(const size_t num);

    std::shared_ptr<graphics::CameraPerspective> camera();
    std::unordered_map<size_t, std::shared_ptr<filing::Scene2d>> &layers() noexcept;
    std::vector<std::shared_ptr<StateMachine>> stateMachines() noexcept;

    graphics::Vector2d<float> getGravity() const noexcept;
    void setGravity(const graphics::Vector2d<float> &gravity) noexcept;

    float getPhysicsLayerPos() const noexcept;
    void setPhysicsLayerPos(float) noexcept;

    float getThickness() const noexcept;
    void setThickness(float) noexcept;

    std::shared_ptr<Namespace> globalNamespace();

private:
    float _sliceThikness;
    float _physicsLayerPosition;
    graphics::Vector2d<float> _defaultGravity;
    std::unordered_map<size_t, std::shared_ptr<filing::Scene2d>> _sliceByDistance;
    std::shared_ptr<graphics::CameraPerspective> _perspectiveCamera;
    std::shared_ptr<graphics::light::LightSource> _lamp;
    std::vector<std::shared_ptr<StateMachine>> _stateMachines;
    bool _editingMode = false;
    std::shared_ptr<Namespace> _levelNamespace;
};
} // namespace ample::game::game2d
