#pragma once

#include <fstream>
#include <sstream>

#include "Exception.h"
#include "Debug.h"

namespace ample::graphics
{
enum class normalsMode
{
    FACE,
    VERTEX,
};
}

namespace ample::filing
{

inline
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

inline
void MergeObject(rapidjson::Value &target, rapidjson::Value &source, rapidjson::Value::AllocatorType &allocator)
{
    for (rapidjson::Value::MemberIterator itr = source.MemberBegin(); itr != source.MemberEnd(); ++itr)
    {
        target.AddMember(itr->name, itr->value, allocator);
    }
}

inline
JsonIO::JsonIO(const std::string &jsonStr_)
        : jsonStr(jsonStr_)
{}

inline
std::string JsonIO::getJSONstring() const
{
    return jsonStr;
}

inline
filing::JsonIO JsonIO::updateJsonIO(std::string nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value field;
    field.SetString(rapidjson::StringRef(nameField.c_str()));
    const rapidjson::Value &value = doc[field];

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    value.Accept(writer);
    std::string newStr = sb.GetString();

    JsonIO io(newStr);
    return io;
}


template<>
inline
int JsonIO::read<int>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetInt();
}

template<>
inline
float JsonIO::read<float>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetFloat();
}

template<>
inline
std::string JsonIO::read<std::string>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetString();
}

template<>
inline
ample::graphics::Vector2d<float> JsonIO::read<ample::graphics::Vector2d<float>>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    ample::graphics::Vector2d<float> obj;
    obj.x = itr->value[0].GetFloat();
    obj.y = itr->value[1].GetFloat();

    return obj;
}

template<>
inline
std::vector<ample::graphics::Vector2d<float>>
JsonIO::read<std::vector<ample::graphics::Vector2d<float>>>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    std::vector<ample::graphics::Vector2d<float>> obj;
    for (size_t i = 0; i < itr->value.Size(); ++i)
    {
        obj.push_back({itr->value[i][0].GetFloat(), itr->value[i][1].GetFloat()});
    }
    return obj;
}

template<>
inline
ample::graphics::Vector2d<int> JsonIO::read<ample::graphics::Vector2d<int>>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    ample::graphics::Vector2d<int> obj;
    obj.x = itr->value[0].GetInt();
    obj.y = itr->value[1].GetInt();
    return obj;
}

template<>
inline
ample::graphics::channelMode JsonIO::read<ample::graphics::channelMode>(const std::string &nameField)
{
    std::string value = read < std::string > (nameField);

    ample::graphics::channelMode obj;
    if (value == "RGB")
    {
        obj = ample::graphics::channelMode::RGB;
    }
    else if (value == "RGBA")
    {
        obj = ample::graphics::channelMode::RGBA;
    }
    return obj;
}

template<>
inline
ample::graphics::normalsMode JsonIO::read<ample::graphics::normalsMode>(const std::string &nameField)
{
    std::string value = read < std::string > (nameField);

    ample::graphics::normalsMode obj;
    if (value == "VERTEX")
    {
        obj = ample::graphics::normalsMode::VERTEX;
    }
    else if (value == "FACE")
    {
        obj = ample::graphics::normalsMode::FACE;
    }
    return obj;
}

template<>
inline
glm::mat4 JsonIO::read<glm::mat4>(const std::string &nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    glm::mat4 obj;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            obj[i][j] = itr->value[i][j].GetInt();
        }
    }
    return obj;
}

template<>
inline
void JsonIO::write<int>(const std::string &nameField, const int &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, obj, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<float>(const std::string &nameField, const float &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, obj, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;

}

template<>
inline
void JsonIO::write<std::string>(const std::string &nameField, const std::string &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value val;
    val.SetString(obj.c_str(), doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<ample::graphics::Vector2d<float>>(
        const std::string &nameField, const ample::graphics::Vector2d<float> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value val(rapidjson::Type::kArrayType);
    rapidjson::Value temp;
    temp.SetFloat(obj.x);
    val.PushBack(temp, doc.GetAllocator());
    temp.SetFloat(obj.y);
    val.PushBack(temp, doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<std::vector<ample::graphics::Vector2d<float>>>(
        const std::string &nameField, const std::vector<ample::graphics::Vector2d<float>> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value array(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < obj.size(); ++i)
    {
        rapidjson::Value val(rapidjson::Type::kArrayType);
        rapidjson::Value temp;
        temp.SetFloat(obj[i].x);
        val.PushBack(temp, doc.GetAllocator());
        temp.SetFloat(obj[i].y);
        val.PushBack(temp, doc.GetAllocator());
        array.PushBack(val, doc.GetAllocator());
    }
    doc.AddMember(str, array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void
JsonIO::write<ample::graphics::Vector2d<int>>(const std::string &nameField, const ample::graphics::Vector2d<int> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value val(rapidjson::Type::kArrayType);
    rapidjson::Value temp;
    temp.SetInt(obj.x);
    val.PushBack(temp, doc.GetAllocator());
    temp.SetInt(obj.y);
    val.PushBack(temp, doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<ample::graphics::channelMode>(const std::string &nameField, const ample::graphics::channelMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    if (obj == ample::graphics::channelMode::RGB)
    {
        doc.AddMember(str, "RGB", doc.GetAllocator());
    }
    else if (obj == ample::graphics::channelMode::RGBA)
    {
        doc.AddMember(str, "RGBA", doc.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<ample::graphics::normalsMode>(const std::string &nameField, const ample::graphics::normalsMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    if (obj == ample::graphics::normalsMode::FACE)
    {
        doc.AddMember(str, "FACE", doc.GetAllocator());
    }
    else if (obj == ample::graphics::normalsMode::VERTEX)
    {
        doc.AddMember(str, "VERTEX", doc.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

template<>
inline
void JsonIO::write<glm::mat4>(const std::string &nameField, const glm::mat4 &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value array(rapidjson::Type::kArrayType);
    for (size_t i = 0; i < 4; ++i)
    {
        rapidjson::Value val(rapidjson::Type::kArrayType);
        rapidjson::Value temp;
        for (size_t j = 0; j < 4; ++j)
        {
            temp.SetFloat(obj[i][j]);
            val.PushBack(temp, doc.GetAllocator());
        }
        array.PushBack(val, doc.GetAllocator());
    }
    doc.AddMember(str, array, doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::string newStr(buffer.GetString(), buffer.GetSize());
    jsonStr = newStr;
}

} //namespace ample::filing