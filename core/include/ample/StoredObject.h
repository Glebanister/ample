#pragma once

#include <string>

namespace ample::filing
{
class StoredObject
{
public:
    virtual std::string dump() = 0;
};
} // namespace ample::filing
