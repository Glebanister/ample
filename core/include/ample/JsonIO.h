#pragma once

#include <string>

namespace ample::filing
{

std::string openJSONfile(const std::string &nameFile);

class JsonIO
{
public:
    JsonIO(const std::string &jsonStr_);

    std::string getJSONstring() const;

    template<typename T>
    T read(const std::string &name);

    template<typename T>
    void write(const std::string &nameField, const T &obj);

private:
    std::string jsonStr;
};

} //namespace ample::filing

#include "templates/JsonIO.hpp"

