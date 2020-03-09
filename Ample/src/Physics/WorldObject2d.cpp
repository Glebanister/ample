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
    auto fixture = _fixtures.emplace_back(std::shared_ptr<Fixture>(new Fixture(_body->CreateFixture(&fixtureDef), *this))).get();
    return _fixtures[_fixtures.size() - 1];
}

void WorldObject2d::setZIndex(float z)
{
    zIndex = z;
}

float WorldObject2d::getX() const
{
    return _body->GetPosition().x;
}

float WorldObject2d::getY() const
{
    return _body->GetPosition().y;
}

float WorldObject2d::getZ() const
{
    return zIndex;
}

float WorldObject2d::getAngleX() const
{
    return 0;
}

float WorldObject2d::getAngleY() const
{
    return 0;
}

float WorldObject2d::getAngleZ() const
{
    return _body->GetAngle() * (180.0f / M_PI);
}

float WorldObject2d::getScaleX() const
{
    return 1.0f;
}

float WorldObject2d::getScaleY() const
{
    return 1.0f;
}

float WorldObject2d::getScaleZ() const
{
    return 1.0f;
}
rapidjson::Document WorldObject2d::save(int id)
{
    rapidjson::Value val;
    rapidjson::Document doc;
    auto &allocator = doc.GetAllocator();
    doc.SetObject();

    val.SetString("WorldObject2d", allocator);
    doc.AddMember("name", val, doc.GetAllocator());

    val.SetUint64(id);
    doc.AddMember("id", val, allocator);

    rapidjson::Value position(rapidjson::Type::kArrayType);
    val.SetFloat(_bodyDef.position.x);
    position.PushBack(val, allocator);
    val.SetFloat(_bodyDef.position.y);
    position.PushBack(val, allocator);
    doc.AddMember("position", position, allocator);

    rapidjson::Value vertices(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < _faceArray->verticies().size(); ++i)
    {
        rapidjson::Value coordinate(rapidjson::Type::kArrayType);
        val.SetFloat(_faceArray->verticies()[i].x);
        coordinate.PushBack(val, allocator);
        val.SetFloat(_faceArray->verticies()[i].y);
        coordinate.PushBack(val, allocator);
        vertices.PushBack(coordinate, allocator);
    }
    doc.AddMember("vertices", vertices, allocator);

    return doc;
}

std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> WorldObject2d::load(const rapidjson::Value &doc)
{
    ample::physics::DefWorldObject2d BodyDef;
    BodyDef.setPosition({doc["position"][0].GetFloat(), doc["position"][1].GetFloat()});
    ample::physics::DefWorldObject2d dynamicBodyDef;

    std::vector<ample::graphics::Vector2d<float>> shape;
    for (size_t i = 0; i < doc["vertexes"].Size(); i++)
    {
        shape.push_back(ample::graphics::Vector2d<float>{doc["vertexes"][i][0].GetFloat(), doc["vertexes"][i][1].GetFloat()});
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

    return std::make_pair(doc["id"].GetInt(), obj);
}

} // namespace ample::physics