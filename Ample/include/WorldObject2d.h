#pragma once

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "WorldLayer2d.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

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
class WorldObject2d;

class Fixture final
{
public:
    WorldObject2d &getObject();

    void setDensity(float density);

    void setFriction(float friction);

    void setRestitution(float restitution);

    void setSensor(bool sensor);

private:
    friend WorldObject2d;

    Fixture(b2Fixture *fixture, WorldObject2d &wObject);

    b2Fixture *_fixture = nullptr;
    WorldObject2d &worldObject;
};

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

    rapidjson::Document save(int id);
    static std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> load(const rapidjson::Value &doc);

    void createPhysicalShape(const std::vector<ample::graphics::Vector2d<float>> &shape);
    b2Body *_body = nullptr;
    std::shared_ptr<Fixture> addFixture(const std::vector<ample::graphics::Vector2d<float>> &shape);
private:
    friend ample::physics::WorldLayer2d;

    std::vector<std::shared_ptr<Fixture>> _fixtures;
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
