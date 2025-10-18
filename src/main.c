/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "Settings.h"
#include "app.h"
#include "button.h"
#include "logger.h"
#include "utils.h"
#include "input.h"
#include "resource_manager.h"
#include "text.h"

#if 1
int main() {
    log_message(LOG_LEVEL_INFO, "Starting up app %s", APP_NAME);
    log_message(LOG_LEVEL_DEBUG, "Debug mode is enabled");

    int exitStatus = init();

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

    SDL_AudioDeviceID audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!audioDevice) {
        error("Unable to open audio device: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_AudioSpec audioSpec;
    if (!SDL_GetAudioDeviceFormat(audioDevice, &audioSpec, NULL)) {
        error("Unable to get audio format: %s", SDL_GetError());
        SDL_CloseAudioDevice(audioDevice);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    log_message(LOG_LEVEL_INFO, "Successfully initialized SDL, Window and Renderer. Start looping app...");
    App* app = App_create(window, renderer, &audioSpec);

    if (!app) {
        exit(EXIT_FAILURE);
    }

    TTF_Font* defaultFont = ResourceManager_getDefaultFont(app->manager, 32);

    Button* button = Button_new(app,
        "Start",
        createRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 150, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT),
        Color_rgb(50, 50, 50),
        Color_rgb(0, 0, 0),
        Color_rgb(255, 255, 255),
        defaultFont
        );

    while (app->running) {
        Input_update(app->input);

        if (app->input->quit) {
            app->running = false;
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);
        SDL_RenderClear(renderer);

        SDL_FRect rect = createRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 100, 100);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        Button_render(renderer, button);

        SDL_RenderPresent(app->renderer);

        SDL_Delay(16); // Roughly 60 FPS
    }

    App_quit(app);
    App_destroy(app);
    log_message(LOG_LEVEL_INFO, "App has been closed.");
    return EXIT_SUCCESS;
}
#endif

#if 0
int main() {
    list_dir(FONT_PATH);
}
#endif

