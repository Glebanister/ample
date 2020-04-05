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
} // namespace ample::physics

namespace ample::physics
{
class WorldLayer2d : public ample::graphics::Layer
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity,
                          float z,
                          float thickness,
                          float relativePositionInSlice);
    void setContactListener(ContactListener &listener);

    float getZ() const noexcept;
    float getThickness() const noexcept;
    float getRelativePositionInSlice() const noexcept;

protected:
    friend WorldObject2d;
    friend WorldJoint2d;
    void onActive() override;

    b2Body *addWorldObject(std::shared_ptr<WorldObject2d> obj, b2BodyDef *bodyDef);
    b2Joint *addWorldJoint(std::shared_ptr<WorldJoint2d> joint, b2JointDef *jointDef);

    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    std::vector<std::shared_ptr<WorldJoint2d>> _joints;
    b2World world;
    const float _z;
    const float _thickness;
    const float _relativePositionInSlice;
};
} // namespace ample::physics
