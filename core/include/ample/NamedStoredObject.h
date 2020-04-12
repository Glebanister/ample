#pragma once

#include "NamedObject.h"
#include "StoredObject.h"

namespace ample::filing
{
class NamedStoredObject : public NamedObject, public StoredObject
{
public:
    NamedStoredObject(const std::string &name = "", const std::string &className = ""); // TODO: remove ""
    NamedStoredObject(const JsonIO &input);
    std::string dump(JsonIO output);
};
}
