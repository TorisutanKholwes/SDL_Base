/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Position {
    float x, y;
};

struct Color {
    int r, g, b, a;
};

#define Position_null() Position_new(-1.0f, -1.0f)
Position* Position_new(float x, float y);
void Position_destroy(Position* pos);
bool Position_isNull(const Position* pos);
bool Position_equals(const Position* a, const Position* b);

Color* Color_rgb(int r, int g, int b);
Color* Color_rgba(int r, int g, int b, int a);
Color* Color_hsv(float h, float s, float v);
Color* Color_copy(Color* color);
SDL_Color Color_toSDLColor(Color* color);
void Color_destroy(Color* color);

void safe_free(void** ptr);
int init();
SDL_FRect SDL_CreateRect(float x, float y, float w, float h);
void SDL_RenderStroke(SDL_Renderer* renderer, const SDL_FRect* rect, float thickness);

char* Strdup(const char* str);
bool String_isNullOrEmpty(const char* str);
bool String_equals(const char* a, const char* b);
int String_parseInt(const char* str, int defaultValue);
float String_parseFloat(const char* str, float defaultValue);
bool String_isNumeric(const char* str);