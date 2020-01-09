#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <cstdarg>
#include <cassert>

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
    assert(out);
    assert(err);
    __log_out_file = out;
    __log_err_file = err;
    entitiesCount()++;
}

Logger::Logger(const char *outFilename, const char *errFilename)
{
    assert(outFilename);
    if (!outFilename)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_NULLPTR]);
    }
    __log_out_file = fopen(outFilename, "w");
    assert(__log_out_file);
    if (!__log_out_file)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_FILE_OPENING]);
    }
    if (errFilename)
    {
        __log_err_file = fopen(errFilename, "w");
        assert(__log_err_file);
        if (!__log_err_file)
        {
            throw std::runtime_error(errLogMessage[errLog::ERR_FILE_OPENING]);
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
        throw std::runtime_error(errLogMessage[errLog::ERR_FORMAT]);
    }
    va_list args;
    int done;
    assert(file);
    assert(format);
    va_start(args, format);
    done = vfprintf(file, format, args);
    va_end(args);
    if (done < 0)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_FILE_WRITING]);
    }
    return done;
}

int Logger::logInfo(const char *format, ...)
{
    if (log(__log_out_file, logPrefix[logId::ID_INFO]) == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    assert(__log_out_file);
    assert(format);
    va_start(args, format);
    done = vfprintf(__log_out_file, format, args);
    va_end(args);
    if (done < 0)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_FILE_WRITING]);
    }
    return done;
}

int Logger::logError(const char *format, ...)
{
    if (log(__log_err_file, logPrefix[logId::ID_ERROR]) == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    assert(__log_err_file);
    assert(format);
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    if (done < 0)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_FILE_WRITING]);
    }
    return done;
}

int Logger::logCritical(const char *format, ...)
{
    if (log(__log_err_file, logPrefix[logId::ID_CRITICAL]) == 0)
    {
        return 0;
    }
    va_list args;
    int done;
    assert(__log_err_file);
    assert(format);
    va_start(args, format);
    done = vfprintf(__log_err_file, format, args);
    va_end(args);
    if (done < 0)
    {
        throw std::runtime_error(errLogMessage[errLog::ERR_FILE_WRITING]);
    }
    return done;
}

Logger::~Logger()
{
    entitiesCount()--;
    if (entitiesCount() == 0)
    {
        if (__log_out_file != stdout && __log_out_file != stderr)
        {
            assert(fclose(__log_out_file) != EOF);
        }
        if (__log_err_file != stdout && __log_err_file != stderr)
        {
            assert(fclose(__log_err_file) != EOF);
        }
    }
}
} // namespace os
