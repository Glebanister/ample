#pragma once

#include "WorldLayer2d.h"

#include <string>
#include <unordered_map>

namespace ample::filing
{
class Scene2d : public ample::physics::WorldLayer2d
{
public:
    Scene2d(const std::string &nameFile);

    void saveScene(const std::string &nameFile);

    ample::graphics::GraphicalObject &getElementById(const int &id);

private:
    std::vector<std::shared_ptr<ample::graphics::GraphicalObject>> _objs;
    std::unordered_map<int, std::shared_ptr<ample::graphics::GraphicalObject>> _storage;
};
} // namespace ample::filing