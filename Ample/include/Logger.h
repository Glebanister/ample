#pragma once

#include <SDL2/SDL.h>
#include <cstdio>

namespace os
{
static FILE *__log_out_file(stdout);
static FILE *__log_err_file(stdout);

class Logger
{
public:
    Logger(FILE *out = stdout, FILE *err = stderr);

    static int logInfo(const char *format, ...);
    static int logError(const char *format, ...);
    static int logCritical(const char *format, ...);

private:
    static int log(FILE *file, const char *format, ...);
};
} // namespace os
