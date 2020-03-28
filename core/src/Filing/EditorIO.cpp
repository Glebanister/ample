#include <typeinfo>
#include <vector>

#include "EditorIO.h"
#include "Exception.h"
#include "WorldObject2d.h"

namespace ample::filing
{

std::string openJSONfile(const std::string &nameFile)
{
    std::ifstream inFile(nameFile);
    if (!inFile)
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CRITICAL);
    }
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;
    while (std::getline(inFile, inputLine))
    {
        jsonDocumentBuffer << inputLine << "\n";
    }
    inFile.close();
    return jsonDocumentBuffer.str();
}

EditorIO::EditorIO(const std::string &jsonStr_)
        : jsonStr(jsonStr_)
{}

std::string EditorIO::getString() const
{
    return jsonStr;
}

void EditorIO::JSONreader(const std::string &nameField, int &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetInt();
}


void EditorIO::JSONreader(const std::string &nameField, float &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetFloat();
}

void EditorIO::JSONreader(const std::string &nameField, std::string &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetString();
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<float> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    JSONreader(nameField, obj.x);
    JSONreader(nameField, obj.y);
}

void EditorIO::JSONreader(const std::string &nameField, std::vector<ample::graphics::Vector2d<float>> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    for (size_t i = 0; i < itr->value.Size(); ++i)
    {
        ample::graphics::Vector2d<float> temp;
        JSONreader(nameField, temp);
        obj.push_back(temp);
    }
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<int> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    JSONreader(nameField, obj.x);
    JSONreader(nameField, obj.y);
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::channelMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    std::string temp = "";
    JSONreader(nameField, temp);

    if (temp == "RGB")
    {
        obj = ample::graphics::channelMode::RGB;
    }
    else if (temp == "RGBA")
    {
        obj = ample::graphics::channelMode::RGBA;
    }
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::normalsMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    std::string temp = "";
    JSONreader(nameField, temp);

    if (temp == "SINGLE")
    {
        obj = ample::graphics::normalsMode::SINGLE;
    }
    else if (temp == "VERTEX")
    {
        obj = ample::graphics::normalsMode::VERTEX;
    }
    else if (temp == "FACE")
    {
        obj = ample::graphics::normalsMode::FACE;
    }
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::textureMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    std::string temp = "";
    JSONreader(nameField, temp);

    if (temp == "TILE")
    {
        obj = ample::graphics::textureMode::TILE;
    }
    else if (temp == "STRETCH")
    {
        obj = ample::graphics::textureMode::STRETCH;
    }
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<ample::graphics::textureMode> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    JSONreader(nameField, obj.x);
    JSONreader(nameField, obj.y);
}

} //namespace ample::filing