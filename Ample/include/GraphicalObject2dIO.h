#pragma once

#include "GraphicalObjectIO.h"
#include "GraphicalObject2d.h"

namespace ample::filing
{
class GraphicalObject2dIO : public GraphicalObjectIO
{
public:
    std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj) override;

    RawObject &loadJSONFile(const std::string &dataDoc, RawObject &obj) override;
};
} // namespace ample::filing
