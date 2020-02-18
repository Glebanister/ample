#pragma once

#include <vector>
#include <memory>

namespace graphics
{
class GraphicalObject
{
public:
    virtual void draw();
    void addSubObject(std::shared_ptr<GraphicalObject> object);

protected:
    virtual void drawSelf();
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
};
} // namespace graphics
