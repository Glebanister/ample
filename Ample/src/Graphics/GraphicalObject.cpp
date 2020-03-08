#include "GraphicalObject.h"

namespace ample::graphics
{
void GraphicalObject::addSubObject(GraphicalObject &object)
{
    activity::Behaviour::addBehaviour(object);
    _subObjects.push_back(&object);
}

void GraphicalObject::setRatio(float ratio)
{
    _ratio = ratio;
}

float GraphicalObject::getRatio() const
{
    return _ratio;
}
} // namespace ample::graphics
