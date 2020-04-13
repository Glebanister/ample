#include <iostream>
#include <memory>

#include "Scene2d.h"
#include "Exception.h"
#include "Debug.h"
#include "JsonIO.h"

namespace ample::filing
{

Scene2d::Scene2d(const ample::graphics::Vector2d<float> &gravity,
                 float z,
                 float thickness,
                 float relativePositionInSlice)
    : WorldLayer2d(gravity, z, thickness, relativePositionInSlice),
      _gravity(gravity),
      _zPosition(z),
      _sceneThickness(thickness),
      _relativeSlicePosition(relativePositionInSlice)
{
}

Scene2d::Scene2d(const JsonIO &input)
    : Scene2d(input.read<graphics::Vector2d<float>>("gravity"),
              input.read<float>("z"),
              input.read<float>("thickness"),
              input.read<float>("relative_position_in_slice"))
{
    // DEBUG("load from json file");
    // std::string fileStr = openJSONfile(nameFile);

    // rapidjson::Document config;
    // config.Parse(fileStr.c_str());

    // const rapidjson::Value &data = config["data"];

    // size_t cnt = 0;
    // _objs.resize(data.Size());
    // for (rapidjson::Value::ConstValueIterator itr = data.Begin(); itr != data.End(); ++itr)
    // {
    //     const rapidjson::Value &attribute = *itr;
    //     rapidjson::StringBuffer sb;
    //     rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    //     attribute.Accept(writer);
    //     std::string str = sb.GetString();

    //     rapidjson::Document doc;
    //     doc.Parse(str.c_str());

    //     JsonIO input(str);
    //     std::string name = input.read<std::string>("name");

    //     if (name == "GraphicalObject2d")
    //     {
    //         ample::graphics::GraphicalObject2d obj(input.updateJsonIO("GraphicalObject2d"));
    //         _objs[cnt] = std::make_shared<ample::graphics::GraphicalObject2d>(obj);
    //         addObject(std::static_pointer_cast<graphics::GraphicalObject>(_objs[cnt]));
    //         DEBUG("add GraphicalObject2d");
    //     }
    //     int id = input.read<int>("id");
    //     _storage[id] = _objs[cnt];
    //     cnt++;
    // }
}

std::string Scene2d::dump()
{
    JsonIO output;
    output.write<graphics::Vector2d<float>>("gravity", _gravity);
    output.write<float>("z", _zPosition);
    output.write<float>("thickness", _sceneThickness);
    output.write<float>("relative_position_in_slice", _relativeSlicePosition);
    std::vector<std::string> objectStrings;
    std::vector<std::string> cameraStrings;
    // TODO: iterators
    for (const auto &object : objects())
    {
        objectStrings.push_back(object->dump());
    }
    // for (const auto &camera : _cameras)
    // {
    //     objectStrings.push_back(camera->dump());
    // }
    output.write<std::string>("objects", filing::dumpObjectsVector("", objectStrings));
    output.write<std::string>("cameras", filing::dumpObjectsVector("", cameraStrings));
    return output;
}

float Scene2d::getDistance() const
{
    return _zPosition;
}
} // namespace ample::filing
