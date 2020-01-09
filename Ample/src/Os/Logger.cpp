#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdarg>

#include "Logger.h"

namespace os
{
int &Logger::entitiesCount()
{
    static int count(0);
    return count;
}

Logger::Logger(FILE *out, FILE *err)
{
    __log_out_file = out;
    __log_err_file = err;
    entitiesCount()++;
}

Logger::Logger(const char *outFilename, const char *errFilename)
{
    if (!outFilename)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    __log_out_file = fopen(outFilename, "w");
    if (!__log_out_file)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    if (errFilename)
    {
        __log_err_file = fopen(errFilename, "w");
        if (!__log_err_file)
        {
            throw std::runtime_error(__PRETTY_FUNCTION__);
        }
    }
    entitiesCount()++;
}

int Logger::log(FILE *file, const char *format, ...)
{
    if (!entitiesCount())
    {
        return 0;
    }
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
    if (log(__log_out_file, "INFO: ") == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_out_file, format, args);
    va_end(args);
    return done;
}

int Logger::logError(const char *format, ...)
{
    if (log(__log_err_file, "ERROR: ") == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    return done;
}

int Logger::logCritical(const char *format, ...)
{
    if (log(__log_err_file, "CRITICAL: ") == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    return done;
}

Logger::~Logger()
{
    entitiesCount()--;
    if (entitiesCount() == 0)
    {
        if (__log_out_file != stdout && __log_out_file != stderr)
        {
            fclose(__log_out_file);
        }
        if (__log_err_file != stdout && __log_err_file != stderr)
        {
            fclose(__log_err_file);
        }
    }
}
} // namespace os
