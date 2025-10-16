/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "utils.h"

#include "logger.h"

Position* Position_new(const int x, const int y) {
    Position* pos = calloc(1, sizeof(Position));
    if (!pos) {
        error("Failed to allocate memory for Position");
        return NULL;
    }
    pos->x = x;
    pos->y = y;
    return pos;
}

void Position_destroy(Position* pos) {
    if (!pos) return;
    safe_free((void**)&pos);
}

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
