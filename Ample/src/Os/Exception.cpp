#include <string>
#include <exception>
#include <iostream>

#include "Exception.h"

namespace ample::exception
{

Exception::Exception(const exId &id, const exType &type, const std::string &message)
    : _id(id), _type(type), _message(message) {}

void Exception::report() const
{
    std::string message = exIdInfo[int(_id)] + ' ' + _message;

    if (_type == exType::CASUAL)
    {
        std::cerr << exTypeInfo[int(_type)] << " : " << message << std::endl;
    }
    else if (_type == exType::CRITICAL)
    {
        std::cout << exTypeInfo[int(_type)] << " : " << message << std::endl;
    }
}

const char *Exception::what() const throw()
{
    return _message.c_str();
}

exId Exception::getId() const
{
    return _id;
}

exType Exception::getType() const
{
    return _type;
}

} // namespace exception
