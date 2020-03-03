#pragma once

#include "Scene.h"
#include "GraphicalObject2d.h"
#include "WorldLayer2d.h"

namespace ample::filing
{
class Scene2d : public Scene
{
public:
    explicit Scene2d(const std::string &scenePath);
    graphics::GraphicalObject2d &getElementById(const std::string &id);
};
} // namespace ample::filing
