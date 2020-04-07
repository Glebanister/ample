#pragma once

#include <iostream>

namespace ample::filing
{
class UniqueObject
{
public:
    int getUniqueId() const noexcept;

private:
    int _uniqueId = rand();
};
} // namespace ample::filing
