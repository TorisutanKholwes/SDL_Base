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

    ButtonStyle* style;

    Input* input;

    bool hovered;
    bool pressed;

    EventHandlerFunc onClick;
    EventHandlerFunc onHover;
    EventHandlerFunc onHoverEnd;
};

Button* Button_new(const App* app, const char* label, SDL_FRect rect, ButtonStyle* style);
void Button_destroy(Button* button);
void Button_render(Button* button, SDL_Renderer* renderer);
void Button_setString(Button* button, const char* str);
void Button_setStringf(Button* button, const char* format, ...);
void Button_update(Button* button);
void Button_onClick(Button* button, EventHandlerFunc func);
void Button_onHover(Button* button, EventHandlerFunc func);
void Button_onHoverEnd(Button* button, EventHandlerFunc func);