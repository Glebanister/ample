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

NamedStoredObject::NamedStoredObject(const JsonIO &input,
                                     const game::Namespace &globalNames)
    : NamedObject(input.read<std::string>("name"),
                  input.read<std::string>("className"))
{
    auto knownNames = filing::loadObjectsVector(input.updateJsonIO("namespace").getJSONstring());
    for (const auto &name : knownNames)
    {
        if (!getNamespace().hasName(name))
        {
            throw exception::Exception(exception::exId::UNSPECIFIED,
                                       exception::exType::CASUAL,
                                       "given namespace does not contain name " +
                                           name);
        }
        getNamespace().addObject(globalNames.getObject(name));
    }
}

std::string NamedStoredObject::dump()
{
    JsonIO output;
    output.write<std::string>("name", name());
    output.write<std::string>("className", className());
    std::vector<std::string> subNames;
    for (const auto &[name, object] : getNamespace().getAllNames())
    {
        utils::ignore(object);
        subNames.emplace_back(name);
    }
    return filing::mergeStrings({
        output.getJSONstring(),
        filing::makeField("namespace", filing::dumpObjectsVector(subNames).getJSONstring()),
    });
}
} // namespace ample::filing
