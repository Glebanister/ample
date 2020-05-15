#pragma once

#include <algorithm>
#include <filesystem>

#include "Exception.h"

namespace ample::utils
{
template <class T>
void ignore(const T &) {}

template <typename T>
void limit(T &value, const T &min, const T &max)
{
    value = std::min(max, value);
    value = std::max(min, value);
}

std::string readAllFile(const std::filesystem::path &path);
void tryCreateDirectory(const std::filesystem::path &path);
void tryCreateFile(const std::filesystem::path &path);
void tryOpenFile(const std::filesystem::path &path);
} // namespace ample::utils
