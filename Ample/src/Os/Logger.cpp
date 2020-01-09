#include <cstdio>
#include <stdexcept>

#include "Logger.h"

namespace os
{
Logger::Logger(FILE *out, FILE *err)
{
    __log_out_file = out;
    __log_err_file = err;
}

int Logger::log(FILE *file, const char *format, ...)
{
    if (!format)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(file, format, args);
    va_end(args);
    return done;
}

int Logger::logInfo(const char *format, ...)
{
    log(__log_out_file, "INFO: ");
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_out_file, format, args);
    va_end(args);
    return done;
}

int Logger::logError(const char *format, ...)
{
    log(__log_err_file, "ERROR: ");
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    return done;
}

int Logger::logCritical(const char *format, ...)
{
    log(__log_err_file, "CRITICAL: ");
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    return done;
}
} // namespace os
