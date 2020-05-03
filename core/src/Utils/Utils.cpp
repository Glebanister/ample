#include <fstream>
#include <iostream>

#include "Utils.h"

namespace ample::utils
{
void tryCreateDirectory(const std::filesystem::path &path)
{
    if (!(std::filesystem::exists(path) && std::filesystem::is_directory(path)))
    {
        if (!std::filesystem::create_directory(path))
        {
            throw exception::Exception(exception::exId::UNSPECIFIED,
                                       exception::exType::CASUAL,
                                       "can not create directory: " + std::string(path));
        }
    }
}

void tryCreateFile(const std::filesystem::path &path)
{
    if (std::filesystem::is_directory(path))
    {
        throw exception::Exception(exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "can not create file, it is a directory: " + std::string(path));
    }
    std::ofstream result(path);
    if (!result.good())
    {
        throw exception::Exception(exception::exId::UNSPECIFIED,
                                   exception::exType::CASUAL,
                                   "can not create file: " + std::string(path));
    }
}
} // namespace ample::utils
