#include <unordered_map>
#include <string>

#include "Storage.h"
namespace ample
{
std::string &Storage::getStr(const std::string &key)
{
    return strstr[key];
}
int Storage::getInt(const std::string &key)
{
    return strint[key];
}
void Storage::set(const std::string &key, std::string value)
{
    strstr[key] = value;
}
void Storage::set(const std::string &key, int value)
{
    strint[key] = value;
}
} // namespace ample
