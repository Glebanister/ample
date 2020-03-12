#include "Scene.h"
#include "Scene2d.h"

namespace ample::filing
{
Scene2d::Scene2d(const std::string &scenePath)
{
    std::ifstream in_file(scenePath);
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;

    while (std::getline(in_file, inputLine))
    {
        jsonDocumentBuffer << inputLine << "\n";
    }
    rapidjson::Document config;
    config.Parse(jsonDocumentBuffer.str().c_str());

    const rapidjson::Value &data = config["data"];

    for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        std::string s = sb.GetString();

        rapidjson::Document doc;
        doc.Parse(s.c_str());

//        if (doc["name"] == "WorldObject2d")
//        {
//            std::pair<int, std::shared_ptr<ample::physics::WorldObject2d>> p =
//                    ample::physics::WorldObject2d::load(doc);
//            int id = p.first;
//            std::shared_ptr<ample::physics::WorldObject2d> obj = p.second;
//            storage_[id] = obj;
//        }
    }
}

graphics::GraphicalObject2d &Scene2d::getElementById(int id)
{
    return *(storage_[id]);
}
} // namespace ample::filing
