#pragma once

#include <vector>
#include <memory>

#include "Activity.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Activity
{
public:
    virtual void draw();
    void addSubObject(const GraphicalObject &object);

protected:
    virtual void drawSelf();
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
};
} // namespace graphics
