#pragma once
#include "box2d/b2_distance_joint.h"

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldLayer2d;
class WorldObject2d;
class WorldDistanceJoint2d : public ample::physics::WorldJoint2d
{
public:
    void onActive() override;

    ample::graphics::Vector2d<float> getAnchorA() const override;
    ample::graphics::Vector2d<float> getAnchorB() const override;
    ample::graphics::Vector2d<float> getReactionForce(float inv_dt) const override;
    float getReactionTorque(float inv_dt) const override;

    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setLength(float length);
    float getLength() const;

    void setFrequency(float hz);
    float getFrequency() const;

    /*void SetDampingRatio(float ratio);
	float GetDampingRatio() const;*/
private:
    friend ample::physics::WorldLayer2d;

    WorldDistanceJoint2d(b2DistanceJoint *joint, WorldObject2d &bodyA, WorldObject2d &bodyB,
                         const std::vector<ample::graphics::Vector2d<float>> &shape);
    b2DistanceJoint *_joint = nullptr;
};
} // namespace ample::physics