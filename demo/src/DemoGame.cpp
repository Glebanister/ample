#include "DemoGame.h"
#include "Clock.h"
#include "Vector2d.h"
#include "PerlinNoise.h"
#include "CameraBehavior.h"
#include "SquareBehavior.h"
#include "WorldObject2d.h"
#include <memory>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include <fstream>
#include <sstream>

//this function print in json file WorldObject2d
//this function need in getters
rapidjson::Document WorldObject2d_save(rapidjson::Document& doc) {
    rapidjson::Value json_val;
    rapidjson::Document temp;
    auto& allocator_temp = temp.GetAllocator();

    temp.SetObject();

    json_val.SetString("WorldObject2d", allocator_temp);
    temp.AddMember("name", json_val, doc.GetAllocator());

    json_val.SetUint64(1);
    temp.AddMember("id", json_val, allocator_temp);

    rapidjson::Value position(rapidjson::Type::kArrayType);
    json_val.SetDouble(0.0f);
    position.PushBack(json_val, allocator_temp);
    json_val.SetDouble(-70.0f);
    position.PushBack(json_val, allocator_temp);
    temp.AddMember("position", position, allocator_temp);

    rapidjson::Value vertexs(rapidjson::Type::kArrayType);

    std::vector<ample::graphics::Vector2d<double>> a {
            {-50, -50},
            {-50, 50},
            {50, 50},
            {50, -50},
    };
    for (size_t i = 0; i < a.size(); ++i) {
        rapidjson::Value position1(rapidjson::Type::kArrayType);
        json_val.SetDouble(a[i].x);
        position1.PushBack(json_val, allocator_temp);
        json_val.SetDouble(a[i].y);
        position1.PushBack(json_val, allocator_temp);
        vertexs.PushBack(position1, allocator_temp);
    }

    temp.AddMember("vertexes", vertexs, allocator_temp);

    return temp;
}

//this function create WorldObject2d from file with min requires
//compile with warnings because float != double
void WorldObject2d_load(const rapidjson::Value& doc) {
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({doc["position"][0].GetDouble(), doc["position"][1].GetDouble()});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    std::vector<ample::graphics::Vector2d<double>> a;


    for (size_t i = 0; i < doc["vertexes"].Size(); i++) {
        a.push_back(ample::graphics::Vector2d<double>
                {doc["vertexes"][i][0].GetDouble(), doc["vertexecds"][i][1].GetDouble()});
    }
    std::shared_ptr<ample::physics::WorldObject2d> ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef, (a));
}


DemoGame::DemoGame(ample::window::Window &window)
    : ample::graphics::LayeredWindowActivity(window)
{
    ample::physics::DefWorldObject2d groundBodyDef;
    groundBodyDef.setPosition({0.0f, -70.0f});
    ample::physics::DefWorldObject2d dynamicBodyDef;
    dynamicBodyDef.setBodyType(ample::physics::BodyType::dynamicBody);
    dynamicBodyDef.setPosition({0.0f, 100.0f});
    ground = std::make_shared<ample::physics::WorldObject2d>(groundBodyDef,
                                                             (std::vector<ample::graphics::Vector2d<double>>){
                                                                 {-50, -50},
                                                                 {-50, 50},
                                                                 {50, 50},
                                                                 {50, -50},
                                                             });
    brick = std::make_shared<ample::physics::WorldObject2d>(dynamicBodyDef,
                                                            (std::vector<ample::graphics::Vector2d<double>>){
                                                                {-25, -25},
                                                                {-25, 25},
                                                                {25, 25},
                                                                {25, -25},
                                                            });
    brick->setColor256(100, 256, 100);

    worldLayer.addObject(*brick);
    worldLayer.addObject(*ground);
    worldLayer.addCamera(camera);
    addLayer(worldLayer);
    addActivity(cameraBeh);

    //save data
    {
        rapidjson::Document dataDoc;
        dataDoc.SetObject();
        auto& allocator = dataDoc.GetAllocator();

        rapidjson::Value data(rapidjson::Type::kArrayType);

        data.PushBack(WorldObject2d_save(dataDoc), allocator);

        dataDoc.AddMember("data", data, allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        dataDoc.Accept(writer);

        std::ofstream out_file("data.json");

        std::string json (buffer.GetString(), buffer.GetSize());
        out_file << json;

        out_file.close();
    }

    //load data
    {
        std::ifstream in_file("data.json");
        std::stringstream jsonDocumentBuffer;
        std::string inputLine;

        while (std::getline(in_file, inputLine)) {
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

            if (doc["name"] == "WorldObject2d") {
                WorldObject2d_load(doc);
            }
//            else
        }
    }

}

void DemoGame::onActive()
{
    LayeredWindowActivity::onActive();
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_LEFT))
    {
        brick->_body->ApplyLinearImpulseToCenter({-100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_RIGHT))
    {
        brick->_body->ApplyLinearImpulseToCenter({100, 0}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_UP))
    {
        brick->_body->ApplyLinearImpulseToCenter({0, 100}, true);
    }
    if (eventManager->keyboard()->isKeyDown(ample::control::keysym::ARROW_DOWN))
    {
        brick->_body->ApplyLinearImpulseToCenter({0, -100}, true);
    }
}
