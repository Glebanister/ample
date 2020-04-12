#include "StoredNamedObject.h"

namespace ample::game
{
StoredNamedObject::StoredNamedObject(const std::string &className, const std::string &name)
    : NamedObject(className, name) {}

std::string StoredNamedObject::dump(filing::JsonIO output, const std::string &fieldName)
{
    output.write("class", className());
    output.write("name", name());
    return output.getJSONstring();
}
} // namespace ample::game
