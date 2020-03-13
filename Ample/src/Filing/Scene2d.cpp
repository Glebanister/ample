#include <typeinfo>
#include <iostream>

#include "Scene2d.h"
#include "WorldObject2dIO.h"


namespace ample::filing
{
Scene2d::Scene2d()
        : ample::physics::WorldLayer2d {{0.0, 0.0}} {}

void Scene2d::load(const std::string &name)
{
    std::ifstream inFile(name);
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;

    while (std::getline(inFile, inputLine))
    {
        jsonDocumentBuffer << inputLine << "\n";
    }
    rapidjson::Document config;
    config.Parse(jsonDocumentBuffer.str().c_str());

    const rapidjson::Value &data = config["array"];

    for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr)
    {
        const rapidjson::Value &attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer <rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        std::string str = sb.GetString();

        rapidjson::Document doc;
        doc.Parse(str.c_str());

        if (doc["class"] == "WorldObject2d")
        {
            ample::filing::WorldObject2dIO temp;
            RawObject obj;
            obj = temp.loadJSONFile(str, obj);
            addWorldObject(obj.shape, obj.pos);
        }
    }
}

void Scene2d::saveScene(const std::string &name)
{
    std::ofstream outFile(name);

    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Value array(rapidjson::Type::kArrayType);
    std::vector <std::string> strings;
    for (size_t i = 0; i < _bodies.size(); i++)
    {
        rapidjson::Document docObj(&doc.GetAllocator());
        auto &allocatorObj = docObj.GetAllocator();
        docObj.SetObject();
        std::string str = "";
        if (typeid(*_bodies[i]) == typeid(ample::physics::WorldObject2d))
        {
            ample::filing::WorldObject2dIO temp;
            str = temp.saveJSONFile(std::to_string(i), dynamic_cast<ample::graphics::GraphicalObject &>(*_bodies[i]));
            docObj.Parse(str.c_str());
            docObj.AddMember("class", "WorldObject2d", allocatorObj);
        }
        array.PushBack(docObj, doc.GetAllocator());
    }
    doc.AddMember("array", array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter <rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string str(buffer.GetString(), buffer.GetSize());
    outFile << str;
    outFile.close();
}

ample::graphics::GraphicalObject &Scene2d::getElementById(const std::string id)
{
    return *_storage[id];
}
} // namespace ample::filing
