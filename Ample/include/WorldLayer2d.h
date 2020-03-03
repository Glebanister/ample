#pragma once

#include "box2d/b2_world.h"

#include "Layer.h"
#include "WorldObject2d.h"
#include "Scene2d.h"

namespace ample::physics
{
class WorldObject2d;

class WorldLayer2d final : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity);
    void addObject(WorldObject2d &object);
    void loadScene(const filing::Scene2d &scene);

protected:
    void onActive() override;

private:
    b2World world;
};
} // namespace ample::physics
