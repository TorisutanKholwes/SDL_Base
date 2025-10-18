/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

#define DEFAULT_BUTTON_WIDTH 200.0f
#define DEFAULT_BUTTON_HEIGHT 50.0f

struct Button {
    Text* text;
    SDL_FRect rect;

    Color* border_color;
    Color* fill_color;
    Color* text_color;

    Input* input;

    bool hovered;
    bool pressed;

    EventHandlerFunc onClick;
    EventHandlerFunc onHover;
    EventHandlerFunc onHoverEnd;
};

Button* Button_new(const App* app, const char* label, SDL_FRect rect, Color* border_color, Color* fill_color, Color* text_color, TTF_Font* font);
void Button_destroy(Button* button);
void Button_render(SDL_Renderer* renderer, Button* button);
void Button_update(Button* button);
void Button_onClick(Button* button, EventHandlerFunc func);
void Button_onHover(Button* button, EventHandlerFunc func);
void Button_onHoverEnd(Button* button, EventHandlerFunc func);