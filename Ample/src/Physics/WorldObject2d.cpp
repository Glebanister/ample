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

void DefWorldObject2d::setBodyType(BodyType type)
{
    switch (type)
    {
    case BodyType::staticBody:
        bodyDef.type = b2_staticBody;
        return;
    case BodyType::kinematicBody:
        bodyDef.type = b2_kinematicBody;
        return;
    case BodyType::dynamicBody:
        bodyDef.type = b2_dynamicBody;
        return;
    }
}

void DefWorldObject2d::setPosition(ample::graphics::Vector2d<float> pos)
{
    bodyDef.position.Set(pos.x, pos.y);
}

void DefWorldObject2d::setAngle(float angle)
{
    bodyDef.angle = angle;
}

void DefWorldObject2d::setLinearVelocity(ample::graphics::Vector2d<float> velocity)
{
    bodyDef.linearVelocity.Set(velocity.x, velocity.y);
}

void DefWorldObject2d::setAngularVelocity(float velocity)
{
    bodyDef.angularVelocity = velocity;
}

void DefWorldObject2d::setLinearDumping(float velocity)
{
    bodyDef.linearDamping = velocity;
}

void DefWorldObject2d::setAngularDumping(float velocity)
{
    bodyDef.angularDamping = velocity;
}

void DefWorldObject2d::setAllowSleep(bool b)
{
    bodyDef.allowSleep = b;
}

void DefWorldObject2d::setAwake(bool b)
{
    bodyDef.awake = b;
}

void DefWorldObject2d::setFixedRotation(bool b)
{
    bodyDef.fixedRotation = b;
}

void DefWorldObject2d::setBullet(bool b)
{
    bodyDef.bullet = b;
}

void DefWorldObject2d::setEnabled(bool b)
{
    bodyDef.enabled = b;
}

void DefWorldObject2d::setGravityScale(float scale)
{
    bodyDef.gravityScale = scale;
}

WorldObject2d::WorldObject2d(const DefWorldObject2d &def,
                             const std::vector<ample::graphics::Vector2d<float>> &shape)
    : GraphicalObject2d(shape, 10, 0), _bodyDef(def.bodyDef)
{
} // TODO: remove stub

std::shared_ptr<Fixture> WorldObject2d::addFixture(
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
    _fixtures.emplace_back(std::shared_ptr<Fixture>(new Fixture(_body->CreateFixture(&fixtureDef), *this))).get();
    return _fixtures[_fixtures.size() - 1];
}

void WorldObject2d::setZIndex(float z)
{
    zIndex = z;
}

void WorldObject2d::onActive()
{
    setTranslate({_body->GetPosition().x, _body->GetPosition().y, getZ()});
    setRotate({0.0f, 0.0f, 1.0f}, _body->GetAngle() * 180.0f / M_PI);
}

} // namespace ample::physics
