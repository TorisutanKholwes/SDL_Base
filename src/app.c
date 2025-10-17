/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "app.h"

#include "logger.h"
#include "utils.h"

App* App_create(SDL_Window* window, SDL_Renderer* renderer) {
    App* app = calloc(1, sizeof(App));
    if (!app) {
        error("Failed to allocate memory for App");
        return NULL;
    }
    app->window = window;
    app->renderer = renderer;
    //app->input = Input_create();
    app->running = true;
    return app;
}

void App_destroy(App* app) {
    if (!app) return;
    safe_free((void**)&app);
}
