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
    auto center = _body->GetLocalCenter();
    return graphics::Vector2d<float>(center.x, center.y);
}

void WorldObject2d::onActive()
{
    setTranslate({_body->GetPosition().x, _body->GetPosition().y, getZ()});
    setRotate({0.0f, 0.0f, 1.0f}, _body->GetAngle() * 180.0f / M_PI);
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

    return doc;*/
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

    return std::make_pair(doc["id"].GetInt(), obj);*/
}

} // namespace ample::physics
