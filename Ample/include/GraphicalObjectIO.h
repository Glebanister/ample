#pragma once

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "GraphicalObject.h"

namespace ample::filing
{
class GraphicalObjectIO
{
public:
    virtual std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj);

    std::pair<int, std::shared_ptr<ample::graphics::GraphicalObject>> loadJSONFile(const rapidjson::Value &doc);
};
} // namespace ample::filing
