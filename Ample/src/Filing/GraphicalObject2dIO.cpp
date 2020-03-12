#include <iostream>

#include "GraphicalObject2dIO.h"
#include "Debug.h"


namespace ample::filing
{
std::string GraphicalObject2dIO::saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj)
{
    std::string str = GraphicalObjectIO::saveJSONFile(name, obj);
    rapidjson::Value val;
    rapidjson::Document doc;
    auto &allocator = doc.GetAllocator();
    doc.SetObject();
    doc.Parse(str.c_str());


    ample::graphics::GraphicalObject2d &newObj = dynamic_cast<ample::graphics::GraphicalObject2d &>(obj);
    rapidjson::Value vertices(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < newObj._faceArray->verticies().size(); ++i)
    {
        rapidjson::Value coordinate(rapidjson::Type::kArrayType);
        val.SetFloat(newObj._faceArray->verticies()[i].x);
        coordinate.PushBack(val, allocator);
        val.SetFloat(newObj._faceArray->verticies()[i].y);
        coordinate.PushBack(val, allocator);
        vertices.PushBack(coordinate, allocator);
    }
    doc.AddMember("vertices", vertices, allocator);


    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string new_str(buffer.GetString(), buffer.GetSize());

    return new_str;
}
} // namespace ample::filing