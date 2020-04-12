#pragma once

#include <stirng>

#include "StoredObject.h"
#include "NamedObject.h"

namespace ample::game
{
class StoredNamedObject : public filing::StoredObject, public NamedObject
{
public:
    StoredNamedObject(const std::string &className, const std::string &name);

    std::string dump(JsonIO output, const std::string &fieldName);
};
} // namespace ample::game
