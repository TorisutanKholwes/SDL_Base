/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"
#include "utils.h"
#include "list.h"
#include "map.h"

#define MAX_KEY_DOWN 256

typedef struct {
    List* keysDown;
    SDL_Scancode lastPressed;
    Map* eventHandlers;
    Position* mousePos;
    bool mouse_left, mouse_right;
    bool shift, ctrl, alt;
    bool esc;
    bool quit;
} Input;

Input* create_input();
void destroy_input(Input* input);
void update_input(Input* input);
bool is_key_down(Input* input, SDL_Scancode key);
bool mouse_in_rect(Input* input, SDL_Rect rect);