#pragma once

#include "GraphicalObject2d.h"
#include "WorldLayer2d.h"
#include "Scene.h"


#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

namespace ample::physics
{
    class WorldLayer2d;
}

namespace ample::filing
{
class Scene2d : public Scene
{
public:
    explicit Scene2d(const std::string &scenePath);
    graphics::GraphicalObject2d &getElementById(int id);

private:
    friend ample::physics::WorldLayer2d;

    std::map<int, std::shared_ptr<ample::graphics::GraphicalObject2d>> storage_;
};
} // namespace ample::filing
