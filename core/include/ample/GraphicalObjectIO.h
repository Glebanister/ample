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
struct RawObject
{
    std::vector<ample::graphics::Vector2d<float>> shape;
    ample::graphics::Vector2d<float> pos;
};

class GraphicalObjectIO
{
public:
    virtual std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj);

    virtual RawObject &loadJSONFile(const std::string &dataDoc, RawObject &obj) = 0;

};
} // namespace ample::filing
