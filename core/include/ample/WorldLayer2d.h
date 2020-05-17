#pragma once

#include <memory>

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
class WorldContact2d;
class WorldJoint2d;
class ContactListener;
} // namespace ample::physics

namespace ample::physics
{
class WorldLayer2d : public ample::graphics::Layer, public std::enable_shared_from_this<WorldLayer2d>
{
public:
    explicit WorldLayer2d(const ample::graphics::Vector2d<float> &gravity,
                          float z,
                          float thickness,
                          float relativePositionInSlice,
                          std::shared_ptr<game::Namespace>);
    void setContactListener(ContactListener &listener);
    void addWorldObject(std::shared_ptr<WorldObject2d> obj);

    float getZ() const noexcept;
    float getThickness() const noexcept;
    float getRelativePositionInSlice() const noexcept;

    WorldContact2d getContactList();

    void clearForces();

    WorldObject2d &getBodyList();
    const WorldObject2d &getBodyList() const;

    WorldJoint2d &getJointList();
    const WorldJoint2d &getJointList() const;

    void setAllowSleeping(bool flag);
    bool getAllowSleeping() const;

    void setGravity(const b2Vec2& gravity);
	
    b2Vec2 getGravity() const;

    bool isLocked() const;

    void setAutoClearForces(bool flag);

    bool getAutoClearForces() const;

    void shiftOrigin(const b2Vec2& newOrigin);

protected:
    friend WorldObject2d;
    friend WorldJoint2d;
    void onActive() override;

    b2Joint *addWorldJoint(std::shared_ptr<WorldJoint2d> joint, b2JointDef *jointDef);

    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    std::vector<std::shared_ptr<WorldJoint2d>> _joints;
    b2World world;
    const float _z;
    const float _thickness;
    const float _relativePositionInSlice;
};
} // namespace ample::physics
