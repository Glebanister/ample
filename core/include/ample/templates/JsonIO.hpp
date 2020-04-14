#pragma once

#define GLM_ENABLE_EXPERIMENTAL

namespace ample::graphics
{
enum class normalsMode;
enum class channelMode;
enum class texturePlayback;
enum class textureOrigin;
} // namespace ample::graphics

namespace ample::physics
{
enum class BodyType;
} // namespace ample::physics

namespace ample::filing
{
inline std::string openJSONfile(const std::string &nameFile)
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

inline void mergeObject(rapidjson::Value &target, rapidjson::Value &source, rapidjson::Value::AllocatorType &allocator)
{
    for (rapidjson::Value::MemberIterator itr = source.MemberBegin(); itr != source.MemberEnd(); ++itr)
    {
        target.AddMember(itr->name, itr->value, allocator);
    }
}

inline std::string makeField(std::string nameField, std::string jsonStr)
{
    rapidjson::Document doc;
    doc.SetObject();

    rapidjson::Document data;
    data.SetObject();

    data.Parse(jsonStr.c_str());

    rapidjson::Value name;
    name.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(name, data, doc.GetAllocator());

    return giveStringDocument(doc) + '\n';
}

inline std::string mergeStrings(const std::vector<std::string> &strings)
{
    if (!strings.size())
    {
        return "";
    }

    rapidjson::Document first, second;
    first.SetObject();
    second.SetObject();

    first.Parse(strings[0].c_str());
    for (size_t i = 1; i < strings.size(); ++i)
    {
        second.Parse(strings[i].c_str());
        mergeObject(first, second, first.GetAllocator());
    }

    return giveStringDocument(first);
}

inline std::string giveStringDocument(rapidjson::Value &doc)
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    doc.Accept(writer);
    return sb.GetString();
}

inline std::string dumpObjectsVector(const std::vector<std::string> &objs)
{
    // rapidjson::Document doc;
    // doc.SetObject();

    // rapidjson::Value array(rapidjson::Type::kArrayType);
    // for (size_t i = 0; i < objs.size(); ++i)
    // {
    //     rapidjson::Document temp;
    //     temp.SetObject();

    //     temp.Parse(objs[i].c_str());
    //     array.PushBack(temp, doc.GetAllocator());
    // }

    // return giveStringDocument(array);
    std::string res;
    for (const auto &str : objs)
    {
        res += str;
    }
    return res;
}

inline std::vector<std::string> loadObjectsVector(const std::string &jsonStr)
{
    std::vector<std::string> objects;
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());
    for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
    {
        const rapidjson::Value &attribute = *itr;
        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
        attribute.Accept(writer);
        objects.emplace_back(sb.GetString());
    }
    return objects;
}

inline JsonIO::JsonIO(const std::string &jsonStr_)
    : jsonStr(jsonStr_)
{
}

inline std::string JsonIO::getJSONstring() const
{
    return jsonStr;
}

inline JsonIO::operator std::string() const noexcept
{
    return jsonStr;
}

inline filing::JsonIO JsonIO::updateJsonIO(std::string nameField)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value field;
    field.SetString(rapidjson::StringRef(nameField.c_str()));
    rapidjson::Value &value = doc[field];

    return JsonIO{giveStringDocument(value)};
}

template <>
inline int JsonIO::read<int>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetInt();
}

template <>
inline size_t JsonIO::read<size_t>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetUint();
}

template <>
inline physics::BodyType JsonIO::read<physics::BodyType>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return static_cast<physics::BodyType>(itr->value.GetInt());
}

template <>
inline float JsonIO::read<float>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetFloat();
}

template <>
inline std::string JsonIO::read<std::string>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    return itr->value.GetString();
}

template <>
inline ample::graphics::Vector2d<float> JsonIO::read<ample::graphics::Vector2d<float>>(const std::string &nameField) const
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

template <>
inline ample::graphics::Vector3d<float> JsonIO::read<ample::graphics::Vector3d<float>>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    ample::graphics::Vector3d<float> obj;
    obj.x = itr->value[0].GetFloat();
    obj.y = itr->value[1].GetFloat();
    obj.z = itr->value[2].GetFloat();

    return obj;
}

template <>
inline ample::graphics::Vector2d<size_t> JsonIO::read<ample::graphics::Vector2d<size_t>>(const std::string &nameField) const
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    ample::graphics::Vector2d<size_t> obj;
    obj.x = itr->value[0].GetUint();
    obj.y = itr->value[1].GetUint();

    return obj;
}

template <>
inline std::vector<ample::graphics::Vector2d<float>>
JsonIO::read<std::vector<ample::graphics::Vector2d<float>>>(const std::string &nameField) const
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

template <>
inline ample::graphics::Vector2d<int> JsonIO::read<ample::graphics::Vector2d<int>>(const std::string &nameField) const
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

template <>
inline ample::graphics::channelMode JsonIO::read<ample::graphics::channelMode>(const std::string &nameField) const
{
    return static_cast<graphics::channelMode>(read<int>(nameField));
}

template <>
inline ample::graphics::normalsMode JsonIO::read<ample::graphics::normalsMode>(const std::string &nameField) const
{
    return static_cast<graphics::normalsMode>(read<int>(nameField));
}

template <>
inline glm::mat4 JsonIO::read<glm::mat4>(const std::string &nameField) const
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

template <>
inline void JsonIO::write<int>(const std::string &nameField, const int &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, obj, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<size_t>(const std::string &nameField, const size_t &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, obj, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<physics::BodyType>(const std::string &nameField, const physics::BodyType &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, static_cast<int>(obj), doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<float>(const std::string &nameField, const float &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, obj, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<std::string>(const std::string &nameField, const std::string &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value val;
    val.SetString(obj.c_str(), doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<ample::graphics::Vector2d<float>>(
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

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<ample::graphics::Vector3d<float>>(
    const std::string &nameField, const ample::graphics::Vector3d<float> &obj)
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
    temp.SetFloat(obj.z);
    val.PushBack(temp, doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<ample::graphics::Vector2d<size_t>>(
    const std::string &nameField, const ample::graphics::Vector2d<size_t> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value val(rapidjson::Type::kArrayType);
    rapidjson::Value temp;
    temp.SetUint(obj.x);
    val.PushBack(temp, doc.GetAllocator());
    temp.SetUint(obj.y);
    val.PushBack(temp, doc.GetAllocator());
    doc.AddMember(str, val, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}



template <>
inline void JsonIO::write<std::vector<ample::graphics::Vector2d<float>>>(
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

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<std::vector<std::string>>(
    const std::string &nameField, const std::vector<std::string> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());

    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));

    rapidjson::Value array(rapidjson::Type::kStringType);
    for (size_t i = 0; i < obj.size(); ++i)
    {
        rapidjson::Value val(rapidjson::Type::kArrayType);
        rapidjson::Value temp;
        temp.SetString(rapidjson::StringRef(obj[i].c_str()));
        val.PushBack(temp, doc.GetAllocator());
        array.PushBack(val, doc.GetAllocator());
    }
    doc.AddMember(str, array, doc.GetAllocator());

    jsonStr = giveStringDocument(doc);
}

template <>
inline void
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

    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<ample::graphics::channelMode>(const std::string &nameField, const ample::graphics::channelMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, static_cast<int>(obj), doc.GetAllocator());
    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<ample::graphics::normalsMode>(const std::string &nameField, const ample::graphics::normalsMode &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value str;
    str.SetString(rapidjson::StringRef(nameField.c_str()));
    doc.AddMember(str, static_cast<int>(obj), doc.GetAllocator());
    jsonStr = giveStringDocument(doc);
}

template <>
inline void JsonIO::write<glm::mat4>(const std::string &nameField, const glm::mat4 &obj)
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

    jsonStr = giveStringDocument(doc);
}

} //namespace ample::filing
