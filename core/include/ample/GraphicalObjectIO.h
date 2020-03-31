#pragma once

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include "GraphicalObject.h"
#include "WorldLayer2d.h"
#include "EditorIO.h"

namespace ample::filing
{
class GraphicalObjectIO
{
public:
    virtual std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj);
};
} // namespace ample::filing
