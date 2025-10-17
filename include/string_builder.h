/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

#define DEFAULT_CAPACITY 64

struct StringBuilder {
    char* data;
    size_t length;
    size_t capacity;
};

StringBuilder* StringBuilder_create(size_t init_capacity);
void StringBuilder_destroy(StringBuilder* builder);
void StringBuilder_append(StringBuilder* builder, const char* str);
void StringBuilder_append_char(StringBuilder* builder, char c);
void StringBuilder_append_int(StringBuilder* builder, int i);
void StringBuilder_append_format(StringBuilder* builder, const char* format, ...);
char* StringBuilder_build(StringBuilder* builder);
void StringBuilder_clear(StringBuilder* builder);
size_t StringBuilder_length(StringBuilder* builder);
size_t StringBuilder_capacity(StringBuilder* builder);