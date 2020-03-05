#pragma once

#include "box2d/b2_world.h"

#include "Layer.h"
#include "Scene2d.h"
#include "WorldObject2d.h"
#include "ContactListener.h"

namespace ample::filing
{
    class Scene2d;
}

namespace ample::physics
{
    class WorldObject2d;
    class ContactListener;
}

namespace ample::physics
{
class WorldLayer2d final : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity);
    void addObject(WorldObject2d &object);
    void loadScene(const ample::filing::Scene2d &scene);
    void setContactListener(ContactListener& listener);
protected:
    void onActive() override;

private:
    b2World world;
};
} // namespace ample::physics
