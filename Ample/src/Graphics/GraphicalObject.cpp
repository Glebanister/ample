#include "GraphicalObject.h"

namespace graphics
{
void GraphicalObject::addSubObject(std::shared_ptr<GraphicalObject> object)
{
    _subObjects.push_back(object);
}
} // namespace graphics
