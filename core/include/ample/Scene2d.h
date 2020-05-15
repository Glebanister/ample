#pragma once

#include <string>
#include <unordered_map>

#include "WorldLayer2d.h"
#include "NamedStoredObject.h"

namespace ample::filing
{
class Scene2d : public ample::physics::WorldLayer2d, public NamedStoredObject
{
public:
    Scene2d(const std::string &name,
            const ample::graphics::Vector2d<float> &gravity,
            float z,
            float thickness,
            float relativePositionInSlice);

    Scene2d(const JsonIO &input, std::shared_ptr<game::Namespace> globalNamespace);
    std::string dump() override;
    float getDistance() const;

private:
    std::vector<std::shared_ptr<ample::graphics::GraphicalObject>> _objs;
    std::unordered_map<int, std::shared_ptr<ample::graphics::GraphicalObject>> _storage;
    const graphics::Vector2d<float> _gravity;
    const float _zPosition;
    const float _sceneThickness;
    const float _relativeSlicePosition;
};
} // namespace ample::filing