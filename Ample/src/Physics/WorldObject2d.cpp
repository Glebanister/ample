#include <cmath>

#include "WorldObject2d.h"
#include "box2d/b2_polygon_shape.h"
#include "Debug.h"
#include <iostream>

namespace ample::physics
{

Fixture::Fixture(b2Fixture *fixture, WorldObject2d &wObject) : _fixture(fixture), worldObject(wObject)
{
    _fixture->SetUserData(this);
    DEBUG(_fixture->GetUserData() == this);
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

PrimaryWorldObject2d::PrimaryWorldObject2d(b2Body *body, const std::vector<ample::graphics::Vector2d<double>> &shape)
    : GraphicalObject2d(shape), _body(body) {}

WorldObject2d::WorldObject2d(b2Body *body, const std::vector<ample::graphics::Vector2d<double>> &shape)
    : PrimaryWorldObject2d(body, shape) {}

auto WorldObject2d::addSubShape(const std::vector<ample::graphics::Vector2d<double>> &shape)
    -> std::shared_ptr<GraphicalObject2d>
{
    _subShapes.emplace_back(new PrimaryWorldObject2d(_body, shape));
    addSubObject(*_subShapes[_subShapes.size() - 1]);
    return _subShapes[_subShapes.size() - 1];
}

std::shared_ptr<Fixture> WorldObject2d::addFixture(
    const std::vector<ample::graphics::Vector2d<double>> &shape)
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
    return _fixtures[_fixtures.size() - 1];
}

void PrimaryWorldObject2d::setZIndex(double z)
{
    zIndex = z;
}

double PrimaryWorldObject2d::getX() const
{
    return _body->GetPosition().x;
}

double PrimaryWorldObject2d::getY() const
{
    return _body->GetPosition().y;
}

double PrimaryWorldObject2d::getZ() const
{
    return zIndex;
}

double PrimaryWorldObject2d::getAngleX() const
{
    return 0;
}

double PrimaryWorldObject2d::getAngleY() const
{
    return 0;
}

double PrimaryWorldObject2d::getAngleZ() const
{
    return _body->GetAngle() * (180 / M_PI);
}

double PrimaryWorldObject2d::getScaleX() const
{
    return 1;
}

double PrimaryWorldObject2d::getScaleY() const
{
    return 1;
}

double PrimaryWorldObject2d::getScaleZ() const
{
    return 1;
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

void WorldObject2d::setBullet(bool flag)
{
    _body->SetBullet(flag);
}

bool WorldObject2d::isBullet() const
{
    return _body->IsBullet();
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
rapidjson::Document WorldObject2d::save(int id)
{
    /*rapidjson::Value val;
    rapidjson::Document doc;
    auto &allocator = doc.GetAllocator();
    doc.SetObject();

    val.SetString("WorldObject2d", allocator);
    doc.AddMember("name", val, doc.GetAllocator());

    val.SetUint64(id);
    doc.AddMember("id", val, allocator);

    rapidjson::Value position(rapidjson::Type::kArrayType);
    val.SetDouble(_bodyDef.position.x);
    position.PushBack(val, allocator);
    val.SetDouble(_bodyDef.position.y);
    position.PushBack(val, allocator);
    doc.AddMember("position", position, allocator);

    rapidjson::Value vertices(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < _graphicalShape.size(); ++i)
    {
        rapidjson::Value coordinate(rapidjson::Type::kArrayType);
        val.SetDouble(_graphicalShape[i].x);
        coordinate.PushBack(val, allocator);
        val.SetDouble(_graphicalShape[i].y);
        coordinate.PushBack(val, allocator);
        vertices.PushBack(coordinate, allocator);
    }
    doc.AddMember("vertices", vertices, allocator);

    return doc;*/
}

std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> WorldObject2d::load(const rapidjson::Value &doc)
{
    /*ample::physics::DefWorldObject2d BodyDef;
    BodyDef.setPosition({doc["position"][0].GetDouble(), doc["position"][1].GetDouble()});
    ample::physics::DefWorldObject2d dynamicBodyDef;

    std::vector<ample::graphics::Vector2d<double>> shape;
    for (size_t i = 0; i < doc["vertexes"].Size(); i++)
    {
        shape.push_back(ample::graphics::Vector2d<double>{doc["vertexes"][i][0].GetDouble(), doc["vertexes"][i][1].GetDouble()});
    }
    ample::physics::BodyType bt;
    if (doc["type"] == 0)
    {
        bt = ample::physics::BodyType::staticBody;
    }
    else if (doc["type"] == 1)
    {
        bt = ample::physics::BodyType::kinematicBody;
    }
    else if (doc["type"] == 2)
    {
        bt = ample::physics::BodyType::dynamicBody;
    }
    BodyDef.setBodyType(bt);
    std::shared_ptr<ample::physics::WorldObject2d> obj = std::make_shared<ample::physics::WorldObject2d>(BodyDef, (shape));

    return std::make_pair(doc["id"].GetInt(), obj);*/
}

} // namespace ample::physics