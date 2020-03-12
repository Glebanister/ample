#pragma once

#include "GraphicalObjectIO.h"
#include "GraphicalObject2d.h"

namespace ample::filing
{
class GraphicalObject2dIO : public GraphicalObjectIO
{
public:
    std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj);

};
} // namespace ample::filing
