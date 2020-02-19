#include "GraphicalObject.h"

namespace ample::graphics
{
void GraphicalObject::addSubObject(std::shared_ptr<GraphicalObject> object)
{
    _subObjects.push_back(object);
}
} // namespace graphics
