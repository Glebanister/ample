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
    template <class TGraphicalObject>
    void addSubObject(const TGraphicalObject &object)
    {
        activity::Activity::addActivity(object);
        _subObjects.push_back(std::make_shared<TGraphicalObject>(object));
    }

protected:
    virtual void drawSelf();
    std::vector<std::shared_ptr<GraphicalObject>> _subObjects;
};
} // namespace ample::graphics
