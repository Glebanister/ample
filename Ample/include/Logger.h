#pragma once

#include <cstdio>

namespace os
{
static FILE *__log_out_file;
static FILE *__log_err_file;

class Logger
{
public:
    Logger(FILE *out = stdout, FILE *err = stderr);
    Logger(const char *outFilename, const char *errFilename = nullptr);

    static int logInfo(const char *format, ...);
    static int logError(const char *format, ...);
    static int logCritical(const char *format, ...);

    ~Logger();

private:
    static int log(FILE *file, const char *format, ...);
    static int &entitiesCount();
};
} // namespace os
