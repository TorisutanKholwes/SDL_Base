/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "app.h"

#include "logger.h"
#include "utils.h"

App* create_app(SDL_Window* window, SDL_Renderer* renderer) {
    App* app = calloc(1, sizeof(App));
    if (!app) {
        error("Failed to allocate memory for App");
        return NULL;
    }
    app->window = window;
    app->renderer = renderer;
    app->running = true;
    return app;
}

void destroy_app(App* app) {
    if (!app) return;
    safe_free((void**)&app);
}
