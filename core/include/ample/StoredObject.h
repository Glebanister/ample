#pragma once

#include <string>

#include "JsonIO.h"

namespace ample::filing
{
class StoredObject
{
public:
    virtual std::string dump(JsonIO output, const std::string &fieldName) = 0;
};
} // namespace ample::filing
