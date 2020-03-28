#include "WorldObject2dIO.h"

#include <iostream>

namespace ample::filing
{
std::string WorldObject2dIO::saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj)
{
    std::string str = GraphicalObject2dIO::saveJSONFile(name, obj);
    rapidjson::Value val;
    rapidjson::Document doc;
    auto &allocator = doc.GetAllocator();
    doc.SetObject();
    doc.Parse(str.c_str());

    ample::physics::WorldObject2d &newObj = dynamic_cast<ample::physics::WorldObject2d &>(obj);

    rapidjson::Value position(rapidjson::Type::kArrayType);
    val.SetFloat(newObj._body->GetPosition().x);
    position.PushBack(val, allocator);
    val.SetFloat(newObj._body->GetPosition().y);
    position.PushBack(val, allocator);
    doc.AddMember("position", position, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string new_str(buffer.GetString(), buffer.GetSize());
    return new_str;
}

RawObject &WorldObject2dIO::loadJSONFile(const std::string &dataDoc, RawObject &obj)
{
    obj = GraphicalObject2dIO::loadJSONFile(dataDoc, obj);
    EditorIO e(dataDoc);
    e.JSONreader("position", obj.pos);
    return obj;
}
} // namespace ample::filing