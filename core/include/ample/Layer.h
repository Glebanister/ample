#pragma once

#include <vector>
#include <memory>

#include "GraphicalObject.h"
#include "Camera.h"
#include "Behaviour.h"
#include "Namespace.h"

namespace ample::graphics
{
class Layer : public activity::Behavior
{
public:
    Layer(std::shared_ptr<game::Namespace>);

    void onActive() override;

    void addCamera(std::shared_ptr<Camera> camera);
    void clearCameras();
    void addObject(std::shared_ptr<GraphicalObject> object);
    void removeObject(std::shared_ptr<GraphicalObject> object);
    void setVisibility(bool) noexcept;
    std::vector<std::shared_ptr<GraphicalObject>> &objects() noexcept;
    std::vector<std::shared_ptr<Camera>> &cameras() noexcept;
    std::shared_ptr<game::Namespace> getNamespace() const noexcept;

protected:
    std::vector<std::shared_ptr<Camera>> _cameras;
    std::vector<std::shared_ptr<GraphicalObject>> _objects;
    bool _visible = true;
    std::shared_ptr<game::Namespace> _levelNamespace;
};
} // namespace ample::graphics
