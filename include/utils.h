/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Position {
    int x, y;
};

struct Color {
    int r, g, b, a;
};

Position* Position_new(int x, int y);
void Position_destroy(Position* pos);

Color* Color_rgb(int r, int g, int b);
Color* Color_rgba(int r, int g, int b, int a);
Color* Color_hsv(float h, float s, float v);
SDL_Color Color_toSDLColor(Color* color);
void Color_destroy(Color* color);

void safe_free(void** ptr);
int init();
SDL_FRect createRect(float x, float y, float w, float h);
char* Strdup(const char* str);