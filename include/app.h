/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    MIX_Mixer* mixer;
    Input* input;
    List* stack;
    Theme* theme;
    ResourceManager* manager;
    bool running;
};

App* App_create(SDL_Window* window, SDL_Renderer* renderer, SDL_AudioSpec *audioSpec);
void App_destroy(App* app);
void App_quit(const App *app);
Frame* App_getCurrentFrame(const App* app);
void App_getCurrentSize(const App* app, int* w, int* h);