/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "utils.h"

void safe_free(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

void quit_sdl(const App *app) {
    MIX_Quit();
    TTF_Quit();
    if (app->window)
        SDL_DestroyWindow(app->window);
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);
    SDL_Quit();
}
