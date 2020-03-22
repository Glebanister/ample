#pragma once

#include "box2d/b2_world.h"

#include "Layer.h"
#include "Scene2d.h"
#include "WorldObject2d.h"
#include "WorldJoint2d.h"
#include "ContactListener.h"

namespace ample::filing
{
class Scene2d;
}

namespace ample::physics
{
class WorldObject2d;
class WorldJoint2d;
class ContactListener;
enum class BodyType
{
    STATIC_BODY = 0,
    KINEMATIC_BODY,
    DYNAMIC_BODY
};
} // namespace ample::physics

namespace ample::physics
{
class WorldLayer2d final : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity);
    //void addWorldObject(WorldObject2d &object);
    WorldObject2d &addWorldObject(const std::vector<ample::graphics::Vector2d<float>> &shape,
                                  ample::graphics::Vector2d<float> pos,
                                  BodyType type = BodyType::STATIC_BODY, float angle = 0);
    WorldJoint2d &addWorldDistanceJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                        ample::graphics::Vector2d<float> anchorOnBodyA,
                                        ample::graphics::Vector2d<float> anchorOnBodyB,
                                        float width = 1,
                                        float length = -1,
                                        bool collideConnected = false);
    WorldJoint2d &addWorldRevoluteJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                        ample::graphics::Vector2d<float> anchor,
                                        float referenceAngle = 0);
    WorldJoint2d &addWorldPrismaticJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                         ample::graphics::Vector2d<float> anchor,
                                         ample::graphics::Vector2d<float> worldAxis = {1, 0},
                                         float referenceAngle = 0);
    void setContactListener(ContactListener &listener);

protected:
    void onActive() override;

private:
    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    std::vector<std::shared_ptr<WorldJoint2d>> _joints;
    b2World world;
};
} // namespace ample::physics