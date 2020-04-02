#pragma once

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

namespace ample::filing
{

std::string openJSONfile(const std::string &nameFile);

void MergeObject(rapidjson::Value &target, rapidjson::Value &source, rapidjson::Value::AllocatorType &allocator);

class JsonIO
{
public:
    JsonIO(const std::string &jsonStr_);

    std::string getJSONstring() const;

    filing::JsonIO updateJsonIO(std::string nameField);

    template<typename T>
    T read(const std::string &name);

    template<typename T>
    void write(const std::string &nameField, const T &obj);

private:
    std::string jsonStr;
};

} //namespace ample::filing

#include "templates/JsonIO.hpp"

