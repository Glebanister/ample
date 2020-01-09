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

enum errLog
{
    ERR_LOG_NO,
    ERR_FILE_OPENING,
    ERR_NULLPTR,
    ERR_FORMAT,
    ERR_FILE_WRITING,
    ERR_FILE_CLOSING,
};

static const char *errLogMessage[] = {
    "Success\n",
    "Can not open file\n",
    "Given pointer is nullified\n",
    "Wrong printf style format\n",
    "Can not close file\n",
};

enum logId
{
    ID_INFO,
    ID_ERROR,
    ID_CRITICAL,
};

static const char *logPrefix[] = {
    "INFO: ",
    "ERROR: ",
    "CRITICAL: ",
};
} // namespace os
