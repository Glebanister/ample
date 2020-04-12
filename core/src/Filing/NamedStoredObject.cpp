#include "NamedStoredObject.h"

namespace ample::filing
{
NamedStoredObject::NamedStoredObject(const std::string &name, const std::string &className)
    : NamedObject(name, className) {}

NamedStoredObject::NamedStoredObject(const JsonIO &input)
    : NamedObject(input.read<std::string>("name"), input.read<std::string>("className")) {}

std::string NamedStoredObject::dump(JsonIO output)
{
    output.write<std::string>("name", name());
    output.write<std::string>("className", className());
}
}
