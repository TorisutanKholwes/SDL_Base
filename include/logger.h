/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

enum LogLevel {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

void log_message(LogLevel level, const char* format, ...);
#define error(msg, ...) log_error(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)
void log_error(const char* file, int line, const char* func, const char* error, ...);
void test_all_log();