#pragma once

#include "WorldLayer2d.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

#include <string>
#include <unordered_map>

namespace ample::filing
{
class Scene2d : public ample::physics::WorldLayer2d
{
public:
    Scene2d();

    void load(const std::string &name);

    void saveScene(const std::string &name);

    ample::graphics::GraphicalObject &getElementById(const std::string &id);

private:
    std::unordered_map <std::string, std::shared_ptr<ample::graphics::GraphicalObject>> _storage;
};
} // namespace ample::filing