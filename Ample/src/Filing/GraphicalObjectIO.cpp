#include "GraphicalObjectIO.h"


namespace ample::filing
{

std::string GraphicalObjectIO::saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj)
{
    rapidjson::Value val;
    rapidjson::Document doc;
    auto &allocator = doc.GetAllocator();
    doc.SetObject();

    val.SetString(name.c_str(), allocator);
    doc.AddMember("name", val, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string str(buffer.GetString(), buffer.GetSize());

    return str;
}

std::pair<int, std::shared_ptr<ample::graphics::GraphicalObject>>
GraphicalObjectIO::loadJSONFile(const rapidjson::Value &doc)
{
//    ample::physics::DefWorldObject2d BodyDef;
//
//    BodyDef.setPosition({doc["position"][0].GetFloat(), doc["position"][1].GetFloat()});
//    ample::physics::DefWorldObject2d dynamicBodyDef;
//
//    std::vector<ample::graphics::Vector2d<float>> shape;
//    for (size_t i = 0; i < doc["vertices"].Size(); i++)
//    {
//        shape.push_back(
//                ample::graphics::Vector2d<float> {doc["vertices"][i][0].GetFloat(), doc["vertexes"][i][1].GetFloat()});
//    }
//
//    ample::physics::BodyType bt;
//    if (doc["type"] == 0)
//    {
//        bt = ample::physics::BodyType::staticBody;
//    }
//    else if (doc["type"] == 1)
//    {
////        static_cast<ample::physics::BodyType>(doc["type"]);
//        bt = ample::physics::BodyType::kinematicBody;
//    }
//    else if (doc["type"] == 2)
//    {
//        bt = ample::physics::BodyType::dynamicBody;
//    }
//    BodyDef.setBodyType(bt);
//
//    std::shared_ptr<ample::physics::WorldObject2d> obj = std::make_shared<ample::physics::WorldObject2d>(BodyDef,
//                                                                                                         (shape));
//
//    return std::make_pair(doc["id"].GetInt(), obj);
}
} // namespace ample::filing