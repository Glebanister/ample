#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "WorldLayer2d.h"
#include "Vector2d.h"
#include "Camera.h"
#include "CameraPerspective.h"
#include "GameController.h"
#include "StoredObject.h"
#include "Scene2d.h"

/*
Level structure:
.
├── transitions                   -- transitions to other levels
├── settings.json                   -- current level settings
├── scenes                          -- all 'slices' of level: foreground, backgrounds
│   └── <...>.json
└── textures                        -- level textures
    └── <...>.[png, jpg, jpeg, bmp]
*/

namespace ample::game::game2d
{

class Level : public ControlledObject::ObjectState<GameController>
{
public:
    Level(const std::string &name, std::shared_ptr<GameController> controller);

    Level(const std::string &name,
          std::shared_ptr<GameController> controller,
          float sliceThikness,
          float physicsLayerPosition,
          const graphics::Vector2d<float> &gravity);

    std::shared_ptr<physics::WorldLayer2d> createSlice(const size_t num);
    std::shared_ptr<physics::WorldLayer2d> frontSlice() noexcept;
    std::shared_ptr<physics::WorldLayer2d> numberedSlice(const size_t num);

    void addGlobalObject(std::shared_ptr<graphics::GraphicalObject>);
    void removeGlobalObject(std::shared_ptr<graphics::GraphicalObject>);

    std::shared_ptr<graphics::CameraPerspective> camera();

    std::unordered_map<size_t, std::shared_ptr<physics::WorldLayer2d>> &layers() noexcept;

private:
    float _sliceThikness;
    float _physicsLayerPosition;
    graphics::Vector2d<float> _defaultGravity;
    std::unordered_map<size_t, std::shared_ptr<filing::Scene2d>> _sliceByDistance;
    std::shared_ptr<graphics::CameraPerspective> _perspectiveCamera;
};
} // namespace ample::game::game2d
