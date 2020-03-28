#include <iostream>

#include "Scene2d.h"
#include "WorldObject2dIO.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::filing
{

Scene2d::Scene2d()
        : ample::physics::WorldLayer2d {{0.0, 0.0}, 0.0, 0.0}
{}

void Scene2d::load(const std::string &nameFile)
{
    std::string buf = openJSONfile(nameFile);
    EditorIO EditorFile(buf);

    rapidjson::Document config;
    config.Parse(buf.c_str());

    const rapidjson::Value &data = config["data"];

    for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr)
    {
        DEBUG("load from json file");
        const rapidjson::Value &attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        std::string str = sb.GetString();

        rapidjson::Document doc;
        doc.Parse(str.c_str());

        EditorIO editorObj(str);
        std::string name = "";
        editorObj.JSONreader(str, name);

        if (name == "WorldObject2d")
        {
            ample::filing::WorldObject2dIO temp;
            RawObject rawObj;
            rawObj = temp.loadJSONFile(str, rawObj);
            addWorldObject(rawObj.shape, rawObj.pos);
            std::string id = "";
            editorObj.JSONreader(str, id);
            _storage[id] = _bodies[_bodies.size() - 1];
        }
    }
}

void Scene2d::saveScene(const std::string &nameFile)
{
    std::ofstream outFile(nameFile);

    rapidjson::Document doc;
    doc.SetObject();
    auto &allocator = doc.GetAllocator();

    rapidjson::Value array(rapidjson::Type::kArrayType);
    std::vector<std::string> strings;
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
        array.PushBack(docObj, allocator);
    }
    doc.AddMember("array", array, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string str(buffer.GetString(), buffer.GetSize());
    outFile << str << '\n';
    outFile.close();
}

ample::graphics::GraphicalObject &Scene2d::getElementById(const std::string &id)
{
    return *_storage[id];
}
} // namespace ample::filing
