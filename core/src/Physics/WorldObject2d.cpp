#include <cmath>

#include "WorldObject2d.h"
#include "box2d/b2_polygon_shape.h"
#include "Debug.h"

namespace ample::physics
{

Fixture::Fixture(b2Fixture *fixture, WorldObject2d &wObject) : _fixture(fixture), worldObject(wObject)
{
    _fixture->SetUserData(this);
}

WorldObject2d &Fixture::getObject()
{
    return worldObject;
}

void Fixture::setDensity(float density)
{
    _fixture->SetDensity(density);
}

void Fixture::setFriction(float friction)
{
    _fixture->SetFriction(friction);
}

void Fixture::setRestitution(float restitution)
{
    _fixture->SetRestitution(restitution);
}

void Fixture::setSensor(bool sensor)
{
    _fixture->SetSensor(sensor);
}

Fixture &WorldObject2d::addFixture(
    const std::vector<ample::graphics::Vector2d<float>> &shape)
{
    b2FixtureDef fixtureDef;
    std::vector<b2Vec2> vertices(shape.size());
    for (size_t i = 0; i < shape.size(); i++)
    {
        vertices[i].Set(shape[i].x, shape[i].y);
    }
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices.data(), shape.size());
    fixtureDef.shape = &polygonShape;
    _fixtures.emplace_back(new Fixture(_body->CreateFixture(&fixtureDef), *this));
    return *(_fixtures.back());
}

void WorldObject2d::setSpeedX(float desiredVelX)
{
    ample::graphics::Vector2d<float> vel = getLinearVelocity();
    float velChangeX = desiredVelX - vel.x;
    float impulseX = getMass() * velChangeX;
    applyLinearImpulseToCenter({impulseX, 0}, true);
}

void WorldObject2d::setSpeedY(float desiredVelY)
{
    ample::graphics::Vector2d<float> vel = getLinearVelocity();
    float velChangeY = desiredVelY - vel.y;
    float impulseY = getMass() * velChangeY;
    applyLinearImpulseToCenter({0, impulseY}, true);
}

void WorldObject2d::onActive()
{
    setTranslate({_body->GetPosition().x, _body->GetPosition().y, getZ()});
    setRotate({0.0f, 0.0f, 1.0f}, _body->GetAngle() * 180.0f / M_PI);
}

void WorldObject2d::setTransform(const graphics::Vector2d<float> &position, float angle)
{
    _body->SetTransform(b2Vec2(position.x, position.y), angle);
}

graphics::Vector2d<float> WorldObject2d::getPosition() const
{
    auto position = _body->GetPosition();
    return graphics::Vector2d<float>(position.x, position.y);
}

float WorldObject2d::getAngle() const
{
    return _body->GetAngle();
}

graphics::Vector2d<float> WorldObject2d::getWorldCenter() const
{
    auto center = _body->GetWorldCenter();
    return graphics::Vector2d<float>(center.x, center.y);
}

graphics::Vector2d<float> WorldObject2d::getLocalCenter() const
{
    auto center = _body->GetLocalCenter();
    return graphics::Vector2d<float>(center.x, center.y);
}

void WorldObject2d::setLinearVelocity(const graphics::Vector2d<float> &v)
{
    _body->SetLinearVelocity({v.x, v.y});
}

graphics::Vector2d<float> WorldObject2d::getLinearVelocity() const
{
    auto velocity = _body->GetLinearVelocity();
    return graphics::Vector2d<float>(velocity.x, velocity.y);
}

void WorldObject2d::setAngularVelocity(float omega)
{
    _body->SetAngularVelocity(omega);
}

float WorldObject2d::getAngularVelocity() const
{
    return _body->GetAngularVelocity();
}

void WorldObject2d::applyForce(const graphics::Vector2d<float> &force, const graphics::Vector2d<float> &point, bool wake)
{
    _body->ApplyForce({force.x, force.y}, {point.x, point.y}, wake);
}

void WorldObject2d::applyForceToCenter(const graphics::Vector2d<float> &force, bool wake)
{
    _body->ApplyForceToCenter({force.x, force.y}, wake);
}

void WorldObject2d::applyTorque(float torque, bool wake)
{
    _body->ApplyTorque(torque, wake);
}

void WorldObject2d::applyLinearImpulse(const graphics::Vector2d<float> &impulse, const graphics::Vector2d<float> &point, bool wake)
{
    _body->ApplyLinearImpulse({impulse.x, impulse.y}, {point.x, point.y}, wake);
}

void WorldObject2d::applyLinearImpulseToCenter(const graphics::Vector2d<float> &impulse, bool wake)
{
    _body->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, wake);
}

void WorldObject2d::applyAngularImpulse(float impulse, bool wake)
{
    _body->ApplyAngularImpulse(impulse, wake);
}

float WorldObject2d::getMass() const
{
    return _body->GetMass();
}

float WorldObject2d::getInertia() const
{
    return _body->GetInertia();
}

graphics::Vector2d<float> WorldObject2d::getWorldPoint(const graphics::Vector2d<float> &localPoint) const
{
    auto point = _body->GetWorldPoint({localPoint.x, localPoint.y});
    return {point.x, point.y};
}

graphics::Vector2d<float> WorldObject2d::getWorldVector(const graphics::Vector2d<float> &localVector) const
{
    auto vec = _body->GetWorldVector({localVector.x, localVector.y});
    return {vec.x, vec.y};
}

graphics::Vector2d<float> WorldObject2d::getLocalPoint(const graphics::Vector2d<float> &worldPoint) const
{
    auto point = _body->GetLocalPoint({worldPoint.x, worldPoint.y});
    return {point.x, point.y};
}

graphics::Vector2d<float> WorldObject2d::getLocalVector(const graphics::Vector2d<float> &worldVector) const
{
    auto vec = _body->GetLocalVector({worldVector.x, worldVector.y});
    return {vec.x, vec.y};
}

graphics::Vector2d<float> WorldObject2d::getLinearVelocityFromWorldPoint(const graphics::Vector2d<float> &worldPoint) const
{
    auto velocity = _body->GetLinearVelocityFromWorldPoint({worldPoint.x, worldPoint.y});
    return {velocity.x, velocity.y};
}

graphics::Vector2d<float> WorldObject2d::getLinearVelocityFromLocalPoint(const graphics::Vector2d<float> &localPoint) const
{
    b2Vec2 velocity = _body->GetLinearVelocityFromLocalPoint({localPoint.x, localPoint.y});
    return {velocity.x, velocity.y};
}

float WorldObject2d::getLinearDamping() const
{
    return _body->GetLinearDamping();
}

void WorldObject2d::setLinearDamping(float linearDamping)
{
    _body->SetLinearDamping(linearDamping);
}

float WorldObject2d::getAngularDamping() const
{
    return _body->GetAngularDamping();
}

void WorldObject2d::setAngularDamping(float angularDamping)
{
    _body->SetAngularDamping(angularDamping);
}

float WorldObject2d::getGravityScale() const
{
    return _body->GetGravityScale();
}

void WorldObject2d::setGravityScale(float scale)
{
    _body->SetGravityScale(scale);
}

void WorldObject2d::setSleepingAllowed(bool flag)
{
    _body->SetSleepingAllowed(flag);
}

bool WorldObject2d::isSleepingAllowed() const
{
    return _body->IsSleepingAllowed();
}

void WorldObject2d::setAwake(bool flag)
{
    _body->SetAwake(flag);
}

bool WorldObject2d::isAwake() const
{
    return _body->IsAwake();
}

void WorldObject2d::setEnabled(bool flag)
{
    _body->SetEnabled(flag);
}

bool WorldObject2d::isEnabled() const
{
    return _body->IsEnabled();
}

void WorldObject2d::setFixedRotation(bool flag)
{
    _body->SetFixedRotation(flag);
}

bool WorldObject2d::isFixedRotation() const
{
    return _body->IsFixedRotation();
}

void WorldObject2d::dump()
{
    _body->Dump();
}

MassData WorldObject2d::getMassData() const
{
    b2MassData massData;
    _body->GetMassData(&massData);
    return {massData.mass, {massData.center.x, massData.center.y}, massData.I};
}

void WorldObject2d::setMassData(const MassData &data)
{
    b2MassData tempData{data.mass, {data.center.x, data.center.y}, data.I};
    _body->SetMassData(&tempData);
}

void WorldObject2d::resetMassData()
{
    _body->ResetMassData();
}

WorldObject2d::WorldObject2d(WorldLayer2d &layer,
                             BodyType type,
                             const std::vector<ample::graphics::Vector2d<float>> &shape,
                             const float relativeThickness,
                             const graphics::Vector2d<float> &faceTextureRepeats,
                             const graphics::Vector2d<float> &sideTextureRepeats,
                             const graphics::normalsMode sideNormalsMode,
                             const std::string &name,
                             const graphics::Vector2d<float> &translated,
                             float rotated)
    : GraphicalObject2d(shape,
                        layer.getThickness() * relativeThickness,
                        layer.getThickness() * layer.getRelativePositionInSlice() - layer.getThickness() * relativeThickness / 2.0f,
                        faceTextureRepeats,
                        sideTextureRepeats,
                        sideNormalsMode,
                        name,
                        translated,
                        rotated),
      _layer(layer)
{
    _bodyDef.position.Set(translated.x, translated.y);
    _bodyDef.angle = rotated;
    switch (type)
    {
    case BodyType::STATIC_BODY:
        _bodyDef.type = b2_staticBody;
        break;
    case BodyType::KINEMATIC_BODY:
        _bodyDef.type = b2_kinematicBody;
        break;
    case BodyType::DYNAMIC_BODY:
        _bodyDef.type = b2_dynamicBody;
        break;
    }
}

WorldLayer2d &WorldObject2d::getWorldLayer() const
{
    return _layer;
}

void WorldObject2d::onAwake()
{
    GraphicalObject2d::onAwake();
    ASSERT(_body);
}
} // namespace ample::physics
