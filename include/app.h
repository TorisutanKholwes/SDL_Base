/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Input* input;
    List* stack;
    bool running;
};

App* App_create(SDL_Window* window, SDL_Renderer* renderer);
void App_destroy(App* app);
void App_quit(const App *app);