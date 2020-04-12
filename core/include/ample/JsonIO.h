#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

#include "Exception.h"
#include "Debug.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "Texture.h"

namespace ample::filing
{
class JsonIO
{
public:
    JsonIO(const std::string &jsonStr_);

    std::string getJSONstring() const;

    JsonIO updateJsonIO(std::string nameField);

    template <typename T>
    T read(const std::string &name) const;

    template <typename T>
    void write(const std::string &nameField, const T &obj);

private:
    std::string jsonStr;
};

std::string openJSONfile(const std::string &nameFile);

void mergeObject(rapidjson::Value &target, rapidjson::Value &source, rapidjson::Value::AllocatorType &allocator);

std::string makeField(std::string nameField, std::string jsonStr);

std::string mergeStrings(std::vector<std::string> &strings);

std::string giveStringDocument(rapidjson::Value &doc);

template <typename T>
std::string saveArrayObjects(std::string nameField, std::vector<T> &objs);

} //namespace ample::filing

#include "templates/JsonIO.hpp"
