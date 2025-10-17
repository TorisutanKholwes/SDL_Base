/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Text {
    char* text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};

Text* Text_new(SDL_Renderer* renderer, TTF_Font* font, const char* str, SDL_Color color);
void Text_destroy(Text* self);
void Text_setString(Text* self, const char* str);
void Text_setColor(Text* self, SDL_Color color);
void Text_render(Text* self, float x, float y);
