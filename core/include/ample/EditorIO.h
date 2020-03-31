#pragma once

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "WorldObject2d.h"

namespace ample::filing
{

std::string openJSONfile(const std::string &nameFile);

class EditorIO
{
public:
    EditorIO(const std::string &jsonStr_);

    std::string getString() const;

    void JSONreader(const std::string &nameField, int &obj);

    void JSONreader(const std::string &nameField, float &obj);

    void JSONreader(const std::string &nameField, std::string &obj);

    void JSONreader(const std::string &nameField, graphics::Vector2d<float> &obj);

    void JSONreader(const std::string &nameField, std::vector<graphics::Vector2d<float>> &obj);

    void JSONreader(const std::string &nameField, graphics::Vector2d<int> &obj);

    void JSONreader(const std::string &nameField, graphics::channelMode &obj);

    void JSONreader(const std::string &nameField, graphics::normalsMode &obj);

    void JSONreader(const std::string &nameField, graphics::textureMode &obj);

    void JSONreader(const std::string &nameField, graphics::Vector2d<graphics::textureMode> &obj);

    graphics::GraphicalObject2dRaw loadGO2d();

private:
    std::string jsonStr;
};

} //namespace ample::filing

