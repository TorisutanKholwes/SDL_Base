/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#include "init.h"
#include "logger.h"

int init_sdl() {
    Uint32 sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

    if (!SDL_Init(sdlFlags)) {
        error("Unable to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!TTF_Init()) {
        error("Unable to initialize SDL_ttf: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!MIX_Init()) {
        error("Unable to initialize SDL_mixer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
