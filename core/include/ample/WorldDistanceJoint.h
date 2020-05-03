#pragma once
#include "box2d/b2_distance_joint.h"
#include <memory>

#include "WorldJoint2d.h"

namespace ample::physics
{
class WorldObject2d;
class WorldDistanceJoint2d : public ample::physics::WorldJoint2d
{
public:
    void onActive() override;

    void setForm(std::shared_ptr<graphics::GraphicalObject2d> form);

    ample::graphics::Vector2d<float> getLocalAnchorA() const;
    ample::graphics::Vector2d<float> getLocalAnchorB() const;

    void setLength(float length);
    float getLength() const;

    void setFrequency(float hz);
    float getFrequency() const;

    void setDampingRatio(float ratio);
    float getDampingRatio() const;

    WorldDistanceJoint2d(const std::name &name,
                         WorldObject2d &bodyA,
                         WorldObject2d &bodyB,
                         const ample::graphics::Vector2d<float> &anchorOnBodyA,
                         const ample::graphics::Vector2d<float> &anchorOnBodyB,
                         float length = -1,
                         bool collideConnected = false);

private:
    std::shared_ptr<graphics::GraphicalObject2d> _form;
    float _initLength;
};
} // namespace ample::physics
