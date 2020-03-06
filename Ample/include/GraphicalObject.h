#pragma once

#include <vector>
#include <memory>

#include "Behaviour.h"

namespace ample::graphics
{
class GraphicalObject : public activity::Behaviour
{
public:
    virtual void draw() = 0;
    void addSubObject(GraphicalObject &object);

protected:
    virtual void drawSelf() = 0;
    std::vector<GraphicalObject *> _subObjects;
};
} // namespace ample::graphics
