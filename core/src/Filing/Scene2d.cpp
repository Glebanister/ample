#include <iostream>
#include <memory>

#include "Scene2d.h"
#include "WorldObject2dIO.h"
#include "Exception.h"
#include "Debug.h"
#include "RegularPolygon.h"

namespace ample::filing
{

Scene2d::Scene2d()
        : ample::physics::WorldLayer2d {{0.0, 0.0}, 0.0, 0.0}
{}

void Scene2d::load(const std::string &nameFile)
{
    DEBUG("load from json file");
    std::string fileStr = openJSONfile(nameFile);

    rapidjson::Document config;
    config.Parse(fileStr.c_str());

    const rapidjson::Value &data = config["data"];

    int cnt = 0;
    objs.resize(data.Size());
    for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr)
    {
        const rapidjson::Value &attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        std::string str = sb.GetString();

        rapidjson::Document doc;
        doc.Parse(str.c_str());

        EditorIO editor(str);
        std::string name = "";
        editor.JSONreader("name", name);

        if (name == "GraphicalObject2d")
        {
            ample::graphics::GraphicalObject2dRaw rawObj = editor.loadGO2d();
            objs[cnt] = std::make_shared<ample::graphics::GraphicalObject2d>(rawObj);
            addObject(*objs[cnt]);
            DEBUG("add GraphicalObject2d");
            std::string id = "";
            editor.JSONreader("id", id);
            _storage[id] = objs[cnt];
        }
        cnt++;
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
