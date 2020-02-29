#pragma once

#include <vector>
#include <memory>

#include "Activity.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Activity
{
public:
    virtual void draw() = 0;
    void addSubObject(std::shared_ptr<GraphicalObject> object);

protected:
    virtual void drawSelf() = 0;
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
};
} // namespace graphics
