#include "GraphicalObject.h"

namespace ample::graphics
{
void GraphicalObject::draw() {}
void GraphicalObject::drawSelf() {}

void GraphicalObject::addSubObject(const GraphicalObject &object)
{
    _subObjects.push_back(std::make_shared<GraphicalObject>(object));
}
} // namespace ample::graphics
