#pragma once

#include "box2d/b2_world.h"

#include "Layer.h"
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
class WorldLayer2d : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity, float z, float thickness);
    //void addWorldObject(WorldObject2d &object);
    WorldObject2d &addWorldObject(const std::vector<ample::graphics::Vector2d<float>> &shape,
                                  ample::graphics::Vector2d<float> pos,
                                  BodyType type = BodyType::STATIC_BODY,
                                  float angle = 0,
                                  float relativeThickness = 1.0);
    WorldJoint2d &addWorldDistanceJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                        ample::graphics::Vector2d<float> anchorOnBodyA,
                                        ample::graphics::Vector2d<float> anchorOnBodyB,
                                        float width = 1,
                                        bool collideConnected = false);
    WorldJoint2d &addWorldRevoluteJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                        ample::graphics::Vector2d<float> anchor,
                                        float referenceAngle = 0);
    WorldJoint2d &addWorldPrismaticJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                         ample::graphics::Vector2d<float> anchor,
                                         ample::graphics::Vector2d<float> worldAxis = {1, 0},
                                         float referenceAngle = 0);
    WorldJoint2d &addWorldPulleyJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                      ample::graphics::Vector2d<float> groundAnchorA,
                                      ample::graphics::Vector2d<float> groundAnchorB,
                                      ample::graphics::Vector2d<float> anchorA,
                                      ample::graphics::Vector2d<float> anchorB,
                                      float lengthA = -1,
                                      float lengthB = -1,
                                      float ratio = 1);
    WorldJoint2d &addWorldGearJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                    WorldJoint2d &jointA, WorldJoint2d &jointB,
                                    float ratio = 1);
    WorldJoint2d &addWorldMouseJoint(WorldObject2d &bodyA, WorldObject2d &bodyB);
    WorldJoint2d &addWorldWheelJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                     ample::graphics::Vector2d<float> anchor,
                                     ample::graphics::Vector2d<float> axis = {1.0, 0.0});
    WorldJoint2d &addWorldWeldJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                    ample::graphics::Vector2d<float> anchor,
                                    float referenceAngle = 0);
    WorldJoint2d &addWorldRopeJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                    ample::graphics::Vector2d<float> localAnchorA,
                                    ample::graphics::Vector2d<float> localAnchorB,
                                    float maxLength);
    void setContactListener(ContactListener &listener);

protected:
    void onActive() override;

    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    std::vector<std::shared_ptr<WorldJoint2d>> _joints;
    b2World world;
    const float _z;
    const float _thickness;
};
} // namespace ample::physics
