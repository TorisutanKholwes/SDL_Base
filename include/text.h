/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Text {
    char* text;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    Position* position;
    TextStyle* style;
    bool fromCenter;
};

Text* Text_new(SDL_Renderer* renderer, TextStyle* style, Position* position, bool fromCenter, const char* str);
Text* Text_newf(SDL_Renderer* renderer, TextStyle* style, Position* position, bool fromCenter, const char* format, ...);
void Text_destroy(Text* self);
void Text_setString(Text* self, const char* str);
void Text_setStringf(Text* self, const char* format, ...);
void Text_setColor(Text* self, Color* color);
void Text_setPosition(Text* self, float x, float y);
void Text_render(Text* self);
Size Text_getSize(Text* self);