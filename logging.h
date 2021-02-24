//
// Created by quangbd on 23/12/2020.
//
#ifndef DEBUG_H
#define DEBUG_H

#include <cstdarg>
#include <iostream>
#include <cstdio>

#ifdef __ANDROID__
#include <android/log.h>
#else
#endif

enum L_LEVEL {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
};

#ifdef DEBUG
static L_LEVEL LOG_LEVEL = LOG_LEVEL_DEBUG;
#else
static L_LEVEL LOG_LEVEL = LOG_LEVEL_INFO;
#endif

const static char *LOG_LEVEL_PREFIX[] =
        {
                "E: ",
                "W: ",
                "I: ",
                "D: "
        };

static void I_LOG(L_LEVEL log_level, const char *file, const char *func, unsigned int line, const char *format, ...) {
    if (log_level > LOG_LEVEL)
        return;

    char message[512];
    va_list args;
    va_start(args, format);
    vsnprintf(message, 512, format, args);
    va_end(args);

#ifdef __ANDROID__
    const char *tag = "cxgboost";
    int android_log_level = ANDROID_LOG_DEBUG;
    switch (log_level) {
        case LOG_LEVEL_INFO:
            android_log_level = ANDROID_LOG_INFO;
            break;
        case LOG_LEVEL_WARNING:
            android_log_level = ANDROID_LOG_WARN;
            break;
        case LOG_LEVEL_ERROR:
            android_log_level = ANDROID_LOG_ERROR;
            break;
        default:
            android_log_level = ANDROID_LOG_DEBUG;
            break;
    }
    __android_log_print(android_log_level, tag, "%s", message);
#else
    if (log_level == LOG_LEVEL_ERROR) {
        std::cerr << file << ":" << line << " " << func << std::endl;
        std::cerr << LOG_LEVEL_PREFIX[log_level] << message << std::endl;
    } else {
        std::cout << LOG_LEVEL_PREFIX[log_level] << message << std::endl;
    }
#endif
}

#define LOG(logLevel, format, ...) \
    I_LOG(logLevel, __BASE_FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
    LOG(LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

#define LOG_WARNING(format, ...) \
    LOG(LOG_LEVEL_WARNING, format, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
    LOG(LOG_LEVEL_INFO, format, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
    LOG(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)

#endif
