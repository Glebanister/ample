#pragma once

#include <vector>
#include <memory>

namespace ample::graphics
{
class GraphicalObject
{
public:
    virtual void draw() = 0;
    void addSubObject(std::shared_ptr<GraphicalObject> object);

protected:
    virtual void drawSelf() = 0;
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
};
} // namespace graphics
