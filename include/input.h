/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"


#define MAX_KEY_DOWN 256

struct Input {
    List* keysDown;
    SDL_Scancode lastPressed;
    Map* eventHandlers;
    Position* mousePos;
    bool mouse_left, mouse_right;
    bool shift, ctrl, alt;
    bool esc;
    bool quit;
};

Input* Input_create();
void Input_destroy(Input* input);
void Input_update(Input* input);
bool Input_keyDown(Input* input, SDL_Scancode key);
bool Input_mouseInRect(Input* input, SDL_Rect rect);