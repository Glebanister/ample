#pragma once

#include <unordered_map>
#include <string>

namespace basic
{
class Storage
{
public:
    std::string &getStr(const std::string &key);
    int getInt(const std::string &key);
    void set(const std::string &key, std::string value);
    void set(const std::string &key, int value);

private:
    std::unordered_map<std::string, int> strint;
    std::unordered_map<std::string, std::string> strstr;
};
} // namespace ample
