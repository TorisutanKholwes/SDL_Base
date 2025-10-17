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
} App;

App* App_create(SDL_Window* window, SDL_Renderer* renderer);
void App_destroy(App* app);