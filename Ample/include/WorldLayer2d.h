#pragma once

#include "Layer.h"
#include "WorldObject2d.h"
#include "box2d/b2_world.h"

namespace ample::physics
{
class WorldObject2d;

class WorldLayer2d final : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity);
    void addObject(WorldObject2d &object);

protected:
    void onActive() override;

private:
    b2World world;
};
} // namespace ample::physics