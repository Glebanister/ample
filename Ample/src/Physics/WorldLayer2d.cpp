#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_body.h"
#include "box2d/b2_joint.h"
#include "box2d/b2_distance_joint.h"

#include "WorldLayer2d.h"
#include "WorldDistanceJoint.h"
#include "Clock.h"
#include "Debug.h"

namespace ample::physics
{
WorldLayer2d::WorldLayer2d(const graphics::Vector2d<float> &gravity)
    : world(b2Vec2(gravity.x, gravity.y)) {}

/*void WorldLayer2d::addWorldObject(WorldObject2d &object)
{
    graphics::Layer::addObject(object);
    object._body = world.CreateBody(&(object._bodyDef));
}*/

void WorldLayer2d::setContactListener(ContactListener &listener)
{
    world.SetContactListener(&listener);
}

WorldObject2d &WorldLayer2d::addWorldObject(const std::vector<ample::graphics::Vector2d<float>> &shape,
                                            ample::graphics::Vector2d<float> pos,
                                            BodyType type, float angle)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    bodyDef.angle = angle;
    switch (type)
    {
    case BodyType::STATIC_BODY:
        bodyDef.type = b2_staticBody;
        break;
    case BodyType::KINEMATIC_BODY:
        bodyDef.type = b2_kinematicBody;
        break;
    case BodyType::DYNAMIC_BODY:
        bodyDef.type = b2_dynamicBody;
        break;
    }
    _bodies.emplace_back(new WorldObject2d(world.CreateBody(&bodyDef), shape));
    graphics::Layer::addObject(*(_bodies[_bodies.size() - 1]));
    return *(_bodies[_bodies.size() - 1]);
}

WorldJoint2d &WorldLayer2d::addWorldDistanceJoint(WorldObject2d &bodyA, WorldObject2d &bodyB,
                                                  ample::graphics::Vector2d<float> anchorOnBodyA,
                                                  ample::graphics::Vector2d<float> anchorOnBodyB,
                                                  float width,
                                                  float length,
                                                  bool collideConnected)
{
    b2DistanceJointDef jointDef;
    jointDef.Initialize(bodyA._body, bodyB._body,
                        {anchorOnBodyA.x, anchorOnBodyA.y},
                        {anchorOnBodyB.x, anchorOnBodyB.y});
    jointDef.collideConnected = collideConnected;
    if (length <= 0)
    {
        length = sqrt(pow(bodyA.getPosition().x - bodyB.getPosition().x, 2) + pow(bodyA.getPosition().y - bodyB.getPosition().y, 2));
    }
    jointDef.length = length;
    std::vector<ample::graphics::Vector2d<float>> distanceLine{{-width / 2, length / 2},
                                                               {width / 2, length / 2},
                                                               {width / 2, -length / 2},
                                                               {-width / 2, -length / 2}};
    _joints.emplace_back(new WorldDistanceJoint2d((b2DistanceJoint *)world.CreateJoint(&jointDef),
                                                  bodyA, bodyB, distanceLine));
    graphics::Layer::addObject(*(_joints[_joints.size() - 1]));
    return *(_joints[_joints.size() - 1]);
}

void WorldLayer2d::onActive()
{
    graphics::Layer::onActive();
    world.Step(1.0 / time::Clock::getFPS(), 8, 3);
}

} // namespace ample::physics