#include "GraphicalObject.h"

namespace ample::graphics
{
void GraphicalObject::addSubObject(GraphicalObject &object)
{
    activity::Activity::addActivity(object);
    _subObjects.push_back(&object);
}
} // namespace ample::graphics
