/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    SDL_Event event;
} App;

App* create_app(SDL_Window* window, SDL_Renderer* renderer);
void destroy_app(App* app);