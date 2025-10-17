/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "app.h"

#include "logger.h"
#include "utils.h"
#include "input.h"
#include "list.h"

App* App_create(SDL_Window* window, SDL_Renderer* renderer) {
    App* app = calloc(1, sizeof(App));
    if (!app) {
        error("Failed to allocate memory for App");
        return NULL;
    }
    app->window = window;
    app->renderer = renderer;
    app->stack = List_create();
    if (!app->stack) {
        error("Failed to create stack list for App");
        safe_free((void**)&app);
        return NULL;
    }
    app->input = Input_create();
    if (!app->input) {
        error("Failed to create Input for App");
        List_destroy(app->stack);
        safe_free((void**)&app);
        return NULL;
    }
    app->running = true;
    return app;
}

void App_destroy(App* app) {
    if (!app) return;
    Input_destroy(app->input);
    List_destroy(app->stack);
    safe_free((void**)&app);
}

void App_quit(const App *app) {
    MIX_Quit();
    TTF_Quit();
    if (app->window)
        SDL_DestroyWindow(app->window);
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);
    SDL_Quit();
}