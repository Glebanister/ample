#pragma once

#include "box2d/b2_world.h"

#include "Layer.h"
#include "WorldObject2d.h"
#include "ContactListener.h"

namespace ample::physics
{
    class WorldObject2d;
    class ContactListener;
    enum class BodyType
{
    STATIC_BODY = 0,
    KINEMATIC_BODY,
    DYNAMIC_BODY
};
}

namespace ample::physics
{
class WorldLayer2d : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity);
    //void addWorldObject(WorldObject2d &object);
    WorldObject2d& addWorldObject(const std::vector<ample::graphics::Vector2d<float>> &shape,
                                            ample::graphics::Vector2d<float> pos,
                                            BodyType type = BodyType::STATIC_BODY, float angle = 0);
    void setContactListener(ContactListener& listener);
protected:
    void onActive() override;

    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    b2World world;
};
} // namespace ample::physics