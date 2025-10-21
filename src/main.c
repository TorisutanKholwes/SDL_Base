/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "Settings.h"
#include "app.h"
#include "frame.h"
#include "logger.h"
#include "utils.h"
#include "input.h"
#include "list.h"
#include "main_frame.h"
#include "resource_manager.h"
#include "style.h"

#if 1
int main() {
    log_message(LOG_LEVEL_INFO, "Starting up app %s", APP_NAME);
    log_message(LOG_LEVEL_DEBUG, "Debug mode is enabled");

    int exitStatus = init();

    if (exitStatus == EXIT_FAILURE) {
        exit(exitStatus);
    };

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;

#if !defined(FULLSCREEN) || (defined(FULLSCREEN) && FULLSCREEN == 1)
    flags |= SDL_WINDOW_FULLSCREEN;
#endif

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

    app->theme = Theme_default(app->manager);

    MainFrame* mainFrame = MainFrame_new(app);
    App_addFrame(app, Frame_new(mainFrame, MainFrame_render, MainFrame_update, MainFrame_focus, MainFrame_unfocus, (FrameDestroyFunc)MainFrame_destroy));


    Uint32 frame_delay = 1000 / FRAME_RATE;

    while (app->running) {
        Uint32 frame_start = SDL_GetTicks();

        Input_update(app->input);

        if (app->input->quit) {
            app->running = false;
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        Color* background = app->theme->background;
        SDL_SetRenderDrawColor(renderer, background->r, background->g, background->b, background->a);
        SDL_RenderClear(renderer);

        Frame* frame = App_getCurrentFrame(app);

        if (!frame) {
            log_message(LOG_LEVEL_WARN, "No current frame to render.");
            continue;
        }

        Frame_update(frame);
        if (app->frameChanged) {
            frame = App_getCurrentFrame(app);
            app->frameChanged = false;
            if (!frame) {
                log_message(LOG_LEVEL_WARN, "No current frame to render after frame change.");
                continue;
            }
        }
        Frame_render(frame, renderer);

        SDL_RenderPresent(app->renderer);

        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    while (List_size(app->stack) > 0) {
        Frame* frame = List_popLast(app->stack);
        Frame_destroy(frame);
    }

    SDL_CloseAudioDevice(audioDevice);

    // Need to be destroyed before App_quit because it uses SDL3 functions
    ResourceManager_destroy(app->manager);

    App_quit(app);
    App_destroy(app);
    log_message(LOG_LEVEL_INFO, "App has been closed.");
    return EXIT_SUCCESS;
}
#endif

#if 0
int main() {
    int a = 5;
    int b = 10;
    List* list = List_create();
    List_push_int(list, a);
    List_push_int(list, b);

    void* val1 = List_getFirst(list);
    if ((int)(long)val1 == 10 || String_equals(val1, "Test")) {
        printf("Val1 is correct: %d\n", (int)(long)val1);
    } else {
        printf("Val1 is incorrect: %d\n", (int)(long)val1);
    }


}
#endif

