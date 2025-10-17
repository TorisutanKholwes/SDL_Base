/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Button {
    Text* text;
    SDL_FRect rect;
    Color* border_color;
    Color* fill_color;
    Color* text_color;
    bool hovered;
    bool pressed;
    Input* input;
};

Button* Button_new(App* app, const char* label, SDL_FRect rect, Color* border_color, Color* fill_color, Color* text_color, TTF_Font* font);
void Button_destroy(Button* button);
void Button_render(SDL_Renderer* renderer, Button* button);
void Button_update(Button* button);
void Button_hover(Input* input, SDL_Event* evt);
void Button_pressed(Input* input, SDL_Event* evt);