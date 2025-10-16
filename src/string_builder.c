/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#include "string_builder.h"

#include "logger.h"
#include "utils.h"

StringBuilder* StringBuilder_create(size_t init_capacity) {
    StringBuilder* builder = calloc(1, sizeof(StringBuilder));
    if (!builder) {
        error("Failed to allocate memory for StringBuilder");
        return NULL;
    }
    builder->capacity = init_capacity > 0 ? init_capacity : DEFAULT_CAPACITY;
    builder->data = calloc(1, builder->capacity);
    if (!builder->data) {
        error("Failed to allocate memory for StringBuilder data");
        safe_free((void**)&builder);
        return NULL;
    }
    builder->length = 0;
    return builder;
}

void StringBuilder_destroy(StringBuilder* builder) {
    if (!builder) return;
    safe_free((void**)&builder->data);
    safe_free((void**)&builder);
}

static bool StringBuilder_ensure_capacity(StringBuilder* builder, size_t new_len) {
    if (new_len + 1 > builder->capacity) {
        size_t new_capacity = builder->capacity * 2;
        while (new_capacity < new_len + 1) {
            new_capacity *= 2;
        }
        char* new_data = realloc(builder->data, new_capacity);
        if (!new_data) {
            error("Failed to reallocate memory for StringBuilder data");
            return false;
        }
        builder->data = new_data;
        builder->capacity = new_capacity;
    }
    return true;
}

void StringBuilder_append(StringBuilder* builder, const char* str) {
    if (!builder || !str) return;
    size_t str_len = strlen(str);
    size_t new_len = builder->length + str_len;
    if (!StringBuilder_ensure_capacity(builder, new_len)) return;
    memcpy(builder->data + builder->length, str, str_len);
    builder->length = new_len;
    builder->data[builder->length] = '\0';
}

void StringBuilder_append_char(StringBuilder* builder, char c) {
    if (!builder) return;

    if (!StringBuilder_ensure_capacity(builder, builder->length + 1)) return;

    builder->data[builder->length++] = c;
    builder->data[builder->length] = '\0';
}

void StringBuilder_append_int(StringBuilder* builder, int i) {
    if (!builder) return;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", i);
    StringBuilder_append(builder, buffer);
}

void StringBuilder_append_format(StringBuilder* builder, const char* format, ...) {
    if (!builder || !format) return;
    va_list args;
    va_start(args, format);
    char buffer[256];
    int needed = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    if (needed < 0) {
        error("StringBuilder_append_format: vsnprintf error");
        return;
    }
    if ((size_t)needed < sizeof(buffer)) {
        StringBuilder_append(builder, buffer);
    } else {
        char* dynamic_buffer = malloc(needed + 1);
        if (!dynamic_buffer) {
            error("Failed to allocate memory for formatted string");
            return;
        }
        va_start(args, format);
        vsnprintf(dynamic_buffer, needed + 1, format, args);
        va_end(args);
        StringBuilder_append(builder, dynamic_buffer);
        safe_free((void**)&dynamic_buffer);
    }
}

char* StringBuilder_build(StringBuilder* builder) {
    if (!builder) return NULL;
    char* result = malloc(builder->length + 1);
    if (!result) {
        error("Failed to allocate memory for StringBuilder build result");
        return NULL;
    }
    memcpy(result, builder->data, builder->length + 1);
    return result;
}

void StringBuilder_clear(StringBuilder* builder) {
    if (!builder) return;
    builder->length = 0;
    if (builder->data) {
        builder->data[0] = '\0';
    }
}

size_t StringBuilder_length(StringBuilder* builder) {
    if (!builder) return 0;
    return builder->length;
}

size_t StringBuilder_capacity(StringBuilder* builder) {
    if (!builder) return 0;
    return builder->capacity;
}