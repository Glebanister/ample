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

struct MassData
{
public:
    WorldObject2d(const DefWorldObject2d &def,
                  const std::vector<ample::graphics::Vector2d<float>> &shape);
    void setZIndex(float z);

    rapidjson::Document save(int id);
    static std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> load(const rapidjson::Value &doc);

    void createPhysicalShape(const std::vector<ample::graphics::Vector2d<float>> &shape);
    b2Body *_body = nullptr;
    std::shared_ptr<Fixture> addFixture(const std::vector<ample::graphics::Vector2d<float>> &shape);
    void onActive() override;

private:
    friend ample::physics::WorldLayer2d;

    std::vector<std::shared_ptr<Fixture>> _fixtures;
    float zIndex = 0;
    b2BodyDef _bodyDef;
};

class WorldObject2d final : public PrimaryWorldObject2d
{
public:
    std::shared_ptr<GraphicalObject2d> addSubShape(const std::vector<ample::graphics::Vector2d<double>> &shape);
    std::shared_ptr<Fixture> addFixture(const std::vector<ample::graphics::Vector2d<double>> &shape);

    void setTransform(const graphics::Vector2d<float> &position, float angle);
    graphics::Vector2d<float> getPosition() const;
    float getAngle() const;
    graphics::Vector2d<float> getWorldCenter() const;
    graphics::Vector2d<float> getLocalCenter() const;
    void setLinearVelocity(const graphics::Vector2d<float> &v);
    graphics::Vector2d<float> getLinearVelocity() const;
    void setAngularVelocity(float omega);
    float getAngularVelocity() const;
    void applyForce(const graphics::Vector2d<float> &force, const graphics::Vector2d<float> &point, bool wake);
    void applyForceToCenter(const graphics::Vector2d<float> &force, bool wake);
    void applyTorque(float torque, bool wake);
    void applyLinearImpulse(const graphics::Vector2d<float> &impulse, const graphics::Vector2d<float> &point, bool wake);
    void applyLinearImpulseToCenter(const graphics::Vector2d<float> &impulse, bool wake);
    void applyAngularImpulse(float impulse, bool wake);
    float getMass() const;
    float getInertia() const;
    MassData getMassData() const;
    void setMassData(const MassData& data);
    void resetMassData();
    graphics::Vector2d<float> getWorldPoint(const graphics::Vector2d<float> &localPoint) const;
    graphics::Vector2d<float> getWorldVector(const graphics::Vector2d<float> &localVector) const;
    graphics::Vector2d<float> getLocalPoint(const graphics::Vector2d<float> &worldPoint) const;
    graphics::Vector2d<float> getLocalVector(const graphics::Vector2d<float> &worldVector) const;
    graphics::Vector2d<float> getLinearVelocityFromWorldPoint(const graphics::Vector2d<float> &worldPoint) const;
    graphics::Vector2d<float> getLinearVelocityFromLocalPoint(const graphics::Vector2d<float> &localPoint) const;
    float getLinearDamping() const;
    void setLinearDamping(float linearDamping);
    float getAngularDamping() const;
    void setAngularDamping(float angularDamping);
    float getGravityScale() const;
    void setGravityScale(float scale);

private:
    friend ample::physics::WorldLayer2d;

    WorldObject2d(b2Body *body, const std::vector<ample::graphics::Vector2d<double>> &shape);
    std::vector<std::shared_ptr<Fixture>> _fixtures;
    std::vector<std::shared_ptr<GraphicalObject2d>> _subShapes;
};
} // namespace ample::physics
