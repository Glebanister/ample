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
                  const std::vector<ample::graphics::Vector2d<double>> &shape);
    void setZIndex(double z);

    double getX() const override;
    double getY() const override;
    double getZ() const override;

    double getAngleX() const override;
    double getAngleY() const override;
    double getAngleZ() const override;

    double getScaleX() const override;
    double getScaleY() const override;
    double getScaleZ() const override;

    rapidjson::Document save(int id);
    static std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> load(const rapidjson::Value& doc);

    void createPhysicalShape(const std::vector<ample::graphics::Vector2d<double>> &shape);
    b2Body *_body = nullptr;

private:
    friend ample::physics::WorldLayer2d;

    double zIndex = 0;
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
