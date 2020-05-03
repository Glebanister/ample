#pragma once

#include "box2d/b2_joint.h"
#include "Behaviour.h"
#include "NamedStoredObject.h"
#include "WorldObject2d.h"
#include "WorldLayer2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldJoint2d : public filing::NamedStoredObject, public activity::Behavior
{
public:
    WorldObject2d &getBodyA();
    WorldObject2d &getBodyB();

    virtual ample::graphics::Vector2d<float> getAnchorA() const;
    virtual ample::graphics::Vector2d<float> getAnchorB() const;

    virtual ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const;

    virtual float getReactionTorque(float inv_dt) const;

    bool isEnabled() const;

    bool getCollideConnected() const;

    WorldJoint2d &getNext();
    const WorldJoint2d &getNext() const;

    std::string dump() override;

protected:
    WorldJoint2d(const std::string &name,
                 const std::string &className,
                 WorldObject2d &bodyA,
                 WorldObject2d &bodyB,
                 b2Joint *joint = nullptr);
    WorldJoint2d(const filing::JsonIO &input,
                 WorldObject2d &bodyA,
                 WorldObject2d &bodyB,
                 b2Joint *joint = nullptr);
    b2Body *getB2Body(WorldObject2d &obj) const;
    b2Joint *getB2Joint(WorldJoint2d &joint) const;
    void initB2Joint(WorldLayer2d &layer, b2JointDef *jointDef);
    b2Joint *_joint = nullptr;
    WorldObject2d &_bodyA;
    WorldObject2d &_bodyB;
};
} // namespace ample::physics
