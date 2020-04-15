#pragma once

#include "NamedObject.h"
#include "StoredObject.h"
#include "JsonIO.h"

namespace ample::filing
{
class NamedStoredObject : public NamedObject, public StoredObject
{
public:
    NamedStoredObject(const std::string &name, const std::string &className);
    NamedStoredObject(const JsonIO &input);
    std::string dump();
};
} // namespace ample::filing
