#pragma once

#include "NamedObject.h"
#include "StoredObject.h"
#include "JsonIO.h"

namespace ample::filing
{
class NamedStoredObject : public NamedObject, public StoredObject
{
public:
    NamedStoredObject(const std::string &name, const std::string &className); // TODO: add std::shared_ptr<Namespace> parentalNamespace
    NamedStoredObject(const JsonIO &input, const game::Namespace &globalNames);
    filing::JsonIO dump();
};
} // namespace ample::filing
