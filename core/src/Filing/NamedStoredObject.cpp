#include "NamedStoredObject.h"
#include "Debug.h"
#include "Exception.h"
#include "Utils.h"

namespace ample::filing
{
NamedStoredObject::NamedStoredObject(const std::string &name, const std::string &className)
    : NamedObject(name, className)
{
}

NamedStoredObject::NamedStoredObject(const JsonIO &input)
    : NamedObject(input.read<std::string>("name"),
                  input.read<std::string>("class_name"),
                  filing::loadObjectsVector(input.updateJsonIO("namespace").getJSONstring()))
{
}

std::string NamedStoredObject::dump()
{
    JsonIO output;
    output.write<std::string>("name", name());
    output.write<std::string>("class_name", className());
    std::vector<std::string> subNames;
    for (const auto &[name, object] : getNamespace().getAllNames())
    {
        utils::ignore(object);
        subNames.emplace_back(name);
    }
    return filing::mergeStrings({output.getJSONstring(),
                                 filing::makeField("namespace", filing::dumpObjectsVector(subNames))});
}
} // namespace ample::filing
