#pragma once

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "WorldLayer2d.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include <memory>

namespace ample::physics
{
enum class BodyType
{
    staticBody = 0,
    kinematicBody,
    dynamicBody
};

struct DefWorldObject2d;
class WorldLayer2d;

class WorldObject2d final : public ample::graphics::GraphicalObject2d
{
public:
    WorldObject2d(const DefWorldObject2d &def,
                  const std::vector<ample::graphics::Vector2d<float>> &shape);
    void setZIndex(float z);

    float getX() const override;
    float getY() const override;
    float getZ() const override;

    float getAngleX() const override;
    float getAngleY() const override;
    float getAngleZ() const override;

    float getScaleX() const override;
    float getScaleY() const override;
    float getScaleZ() const override;

    void createPhysicalShape(const std::vector<ample::graphics::Vector2d<float>> &shape);
    b2Body *_body = nullptr;

private:
    friend ample::physics::WorldLayer2d;

    float zIndex = 0;
    b2BodyDef _bodyDef;
};

struct DefWorldObject2d final
{
    DefWorldObject2d() = default;
    void setBodyType(BodyType type);
    void setPosition(ample::graphics::Vector2d<float> pos);
    void setAngle(float angle);
    void setLinearVelocity(ample::graphics::Vector2d<float> velocity);
    void setAngularVelocity(float velocity);
    void setLinearDumping(float velocity);
    void setAngularDumping(float velocity);
    void setAllowSleep(bool b);
    void setAwake(bool b);
    void setFixedRotation(bool b);
    void setBullet(bool b);
    void setEnabled(bool b);
    void setGravityScale(float scale);

private:
    friend ample::physics::WorldObject2d;
    b2BodyDef bodyDef;
};
} // namespace ample::physics
