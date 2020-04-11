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
class WorldContact2d;
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

    /*
    void SetDestructionListener(b2DestructionListener* listener);
	void SetContactFilter(b2ContactFilter* filter);
    */
	/*
	void DestroyBody(b2Body* body);
	void DestroyJoint(b2Joint* joint);*/
	/*void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;
	void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;
	void SetWarmStarting(bool flag) { m_warmStarting = flag; }
	bool GetWarmStarting() const { return m_warmStarting; }
	void SetContinuousPhysics(bool flag) { m_continuousPhysics = flag; }
	bool GetContinuousPhysics() const { return m_continuousPhysics; }
	void SetSubStepping(bool flag) { m_subStepping = flag; }
	bool GetSubStepping() const { return m_subStepping; }
	int32 GetProxyCount() const;
	int32 GetBodyCount() const;
	int32 GetJointCount() const;
	int32 GetContactCount() const;
	int32 GetTreeHeight() const;
	int32 GetTreeBalance() const;
	float getTreeQuality() const;
	const b2ContactManager& GetContactManager() const;
	const b2Profile& GetProfile() const;
	void Dump();
    */
protected:
    friend WorldObject2d;
    friend WorldJoint2d;
    void onActive() override;

    // b2Body *addWorldObject(std::shared_ptr<WorldObject2d> obj, b2BodyDef *bodyDef);
    b2Joint *addWorldJoint(std::shared_ptr<WorldJoint2d> joint, b2JointDef *jointDef);

    std::vector<std::shared_ptr<WorldObject2d>> _bodies;
    std::vector<std::shared_ptr<WorldJoint2d>> _joints;
    b2World world;
    const float _z;
    const float _thickness;
    const float _relativePositionInSlice;
};
} // namespace ample::physics
