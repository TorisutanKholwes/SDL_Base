/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "Settings.h"
#include "init.h"
#include "logger.h"
#include "utils.h"

#if 1
int main() {
    log_message(LOG_LEVEL_INFO, "Starting up app %s", APP_NAME);
    log_message(LOG_LEVEL_DEBUG, "Debug mode is enabled");

    int exitStatus = init_sdl();

    if (exitStatus == EXIT_FAILURE) {
        exit(exitStatus);
    };

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
        WINDOW_WIDTH, WINDOW_HEIGHT, flags);

    if (!window) {
        error("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        error("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    log_message(LOG_LEVEL_INFO, "Successfully initialized SDL, Window and Renderer. Start looping app...");
    App* app = create_app(window, renderer);
    if (!app) {
        exit(EXIT_FAILURE);
    }

    while (app->running) {
        while (SDL_PollEvent(&app->event)) {
            if (app->event.type == SDL_EVENT_QUIT) {
                app->running = false;
            } else if (app->event.type == SDL_EVENT_KEY_DOWN) {
                if (app->event.key.key == SDLK_ESCAPE) {
                    app->running = false;
                }
            }
        }

        SDL_RenderPresent(app->renderer);

        SDL_Delay(16); // Roughly 60 FPS
    }

    quit_sdl(app);
    destroy_app(app);
    log_message(LOG_LEVEL_INFO, "App has been closed.");
    return EXIT_SUCCESS;
}
#endif

#if 0
int main() {
}
#endif

