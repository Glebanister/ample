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
} // namespace ample::filing