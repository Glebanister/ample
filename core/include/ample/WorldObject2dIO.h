#pragma once

#include "GraphicalObject2dIO.h"
#include "WorldObject2d.h"

namespace ample::filing
{
class WorldObject2dIO : public GraphicalObject2dIO
{
public:
    std::string saveJSONFile(const std::string &name, ample::graphics::GraphicalObject &obj) override;
};
} //namespace ample::filing