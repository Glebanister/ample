#pragma once

#include "box2d/b2_rope_joint.h"
#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldRopeJoint2d : public WorldJoint2d
{
public:
    void onActive() override;

    void setForm(std::shared_ptr<graphics::GraphicalObject2d> form);

    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setMaxLength(float length);
    float getMaxLength() const;

    //b2LimitState getLimitState() const;

    WorldRopeJoint2d(WorldObject2d &bodyA,
                     WorldObject2d &bodyB,
                     const ample::graphics::Vector2d<float> &localAnchorA,
                     const ample::graphics::Vector2d<float> &localAnchorB,
                     float maxLength,
                     bool collideConnected = false);

private:
    std::shared_ptr<graphics::GraphicalObject2d> _form = nullptr;
    float _initLength;
};
} // namespace ample::physics
