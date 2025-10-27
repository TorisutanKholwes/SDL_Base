/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "logger.h"
#include "ansi.h"

#ifndef WIN32
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

char* get_level_color(const LogLevel level) {
    char* buffer = malloc(16);
    switch (level) {
        case LOG_LEVEL_DEBUG:
            sprintf(buffer, "%s", ANSI_COLOR_CYAN);
            break;
        case LOG_LEVEL_INFO:
            sprintf(buffer, "%s", ANSI_COLOR_GREEN);
            break;
        case LOG_LEVEL_WARN:
            sprintf(buffer, "%s", ANSI_COLOR_YELLOW);
            break;
        case LOG_LEVEL_ERROR:
            sprintf(buffer, "%s", ANSI_COLOR_RED);
            break;
        case LOG_LEVEL_FATAL:
            sprintf(buffer, "%s", ANSI_COLOR_MAGENTA);
            break;
        default:
            sprintf(buffer, "%s", ANSI_COLOR_RESET);
            break;
    }
    return buffer;
}

const char* get_level_string(const LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:
            return "[DEBUG]";
        case LOG_LEVEL_INFO:
            return "[INFO]";
        case LOG_LEVEL_WARN:
            return "[WARN]";
        case LOG_LEVEL_ERROR:
            return "[ERROR]";
        case LOG_LEVEL_FATAL:
            return "[FATAL]";
        default:
            return "[UNKNOWN]";
    }
}

void log_message(const LogLevel level, const char* format, ...) {
#ifndef WIN32
    pthread_mutex_lock(&mutex);
    if (level == LOG_LEVEL_DEBUG) {
#if !defined(PRODUCTION) || (defined(PRODUCTION) && PRODUCTION == 1)
        pthread_mutex_unlock(&mutex);
        return;
#endif
    }
#else
    if (level == LOG_LEVEL_DEBUG) {
        return;
    }
#endif
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char datetime[32];
    strftime(datetime, sizeof(datetime)-1, "%Y-%m-%d %H:%M:%S", t);

    const char* levelStr = get_level_string(level);
    char* levelColor = get_level_color(level);

    char msg[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    printf("%s%s %s %s%s\n", levelColor, datetime, levelStr, msg, ANSI_COLOR_RESET);
    free(levelColor);
#ifndef WIN32
    pthread_mutex_unlock(&mutex);
#endif
}

void log_error(const char* file, const int line, const char* func, const char* error, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, error);
    vsnprintf(buffer, sizeof(buffer), error, args);
    va_end(args);

    char final_msg[1096];
    snprintf(final_msg, sizeof(final_msg), "function %s, file %s, line %d\n%s", func, file, line, buffer);

    log_message(LOG_LEVEL_ERROR, "%s", final_msg);
}

void test_all_log() {
    log_message(LOG_LEVEL_DEBUG, "This is a debug message.");
    log_message(LOG_LEVEL_INFO, "This is an info message.");
    log_message(LOG_LEVEL_WARN, "This is a warning message.");
    log_message(LOG_LEVEL_ERROR, "This is an error message.");
    log_message(LOG_LEVEL_FATAL, "This is a fatal message.");
}