#pragma once

#include <string>

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

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

std::string openJSONfile(const std::string &nameFile);

void mergeObject(rapidjson::Value &target, rapidjson::Value &source, rapidjson::Value::AllocatorType &allocator);

std::string makeField(std::string nameField, std::string jsonStr);

std::string mergeStrings(std::vector<std::string> &strings);

std::string giveStringDocument(rapidjson::Value &doc);

class JsonIO
{
public:
    JsonIO(const std::string &jsonStr_);

    std::string getJSONstring() const;

    filing::JsonIO updateJsonIO(std::string nameField);

    template <typename T>
    T read(const std::string &name);

    template <typename T>
    void write(const std::string &nameField, const T &obj);

private:
    std::string jsonStr;
};

} //namespace ample::filing

#include "templates/JsonIO.hpp"
