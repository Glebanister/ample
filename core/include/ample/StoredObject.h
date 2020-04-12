#pragma once

#include "JsonIO.h"

namespace ample::filing
{
class StoredObject
{
public:
    virtual std::string dump(JsonIO output) = 0;
};
} // namespace ample::filing
