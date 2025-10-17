/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "Settings.h"
#include "init.h"
#include "logger.h"
#include "map.h"
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
    App* app = App_create(window, renderer);

    if (!app) {
        exit(EXIT_FAILURE);
    }

    while (app->running) {

        SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);
        SDL_RenderClear(renderer);

        SDL_FRect rect = {270, 190, 100, 100};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(app->renderer);

        SDL_Delay(16); // Roughly 60 FPS
    }

    quit_sdl(app);
    App_destroy(app);
    SDL_Quit();
    log_message(LOG_LEVEL_INFO, "App has been closed.");
    return EXIT_SUCCESS;
}
#endif

#if 0
int main() {

    Map* map = Map_create();
    Map_put_decimal(map, "foo", 100.5f);
    Map_put_decimal(map, "testa", 200.32f);
    Map_put_decimal(map, "test", 300.124f);
    char* mapStr = Map_toString(map, "%s", "%.2f", NULL, NULL);
    log_message(LOG_LEVEL_INFO, "Map contents: %s", mapStr);
    safe_free((void**)&mapStr);
    Map_destroy(map);
    return 0;

}
#endif

