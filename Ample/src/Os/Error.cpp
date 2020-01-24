#include <string>
#include <exception>
#include <iostream>

#include "Error.h"

namespace exception
{

Exception::Exception(const exId &id, const exType &type, const std::string &message)
    : _id(id), _type(type), _message(message) {}

void Exception::report()
{
    std::string message = _message;
    if (_message == "")
    {
        message = exIdInfo[int(_id)];
    }

    if (_type == exType::CASUAL)
    {
        std::cerr << exTypeInfo[int(_type)] << " : " << message << std::endl;
    }
    else if (_type == exType::CRITICAL)
    {
        std::cout << exTypeInfo[int(_type)] << " : " << message << std::endl;
    }
}

exId Exception::getId()
{
    return _id;
}

exType Exception::getType()
{
    return _type;
}

} // namespace exception
