#pragma once

#include <vector>
#include <memory>

#include "GraphicalObject.h"
#include "Camera.h"
#include "Behaviour.h"

namespace ample::graphics
{
class Layer : public activity::Behavior
{
public:
    void onActive() override;

    void addCamera(std::shared_ptr<Camera> camera);
    void clearCameras();

    void addObject(std::shared_ptr<GraphicalObject> object);
    void removeObject(std::shared_ptr<GraphicalObject> object);
    void setVisibility(bool) noexcept;

    size_t objectsCount() const noexcept;

    std::vector<std::shared_ptr<GraphicalObject>> &objects() noexcept;

private:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::vector<std::shared_ptr<GraphicalObject>> _objects;
    bool _visible = true;
};
} // namespace ample::graphics
