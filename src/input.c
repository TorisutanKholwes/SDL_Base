/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "input.h"

#include "logger.h"
#include "list.h"
#include "map.h"
#include "utils.h"

Input* Input_create() {
    Input* input = calloc(1, sizeof(Input));
    if (!input) {
        error("Failed to allocate memory for Input");
        return NULL;
    }
    input->keysDown = List_create();
    if (!input->keysDown) {
        error("Failed to create keysDown list");
        safe_free((void**)&input);
        return NULL;
    }
    input->eventHandlers = Map_create();
    if (!input->eventHandlers) {
        error("Failed to create eventHandlers map");
        List_destroy(input->keysDown);
        safe_free((void**)&input);
        return NULL;
    }
    input->keyEventHandlers = Map_create();
    if (!input->keyEventHandlers) {
        error("Failed to create keyEventHandlers map");
        List_destroy(input->keysDown);
        Map_destroy(input->eventHandlers);
        safe_free((void**)&input);
        return NULL;
    }
    input->mousePos = NULL;
    input->lastPressed = SDL_SCANCODE_UNKNOWN;
    return input;
}

void Input_destroy(Input* input) {
    if (!input) return;
    List_destroy(input->keysDown);
    Map_destroy(input->eventHandlers);
    Position_destroy(input->mousePos);
    safe_free((void**)&input);
}

void Input_update(Input* input) {
    /*List_clear(input->keysDown);
    Map_clear(input->eventHandlers);
    input->lastPressed = SDL_SCANCODE_UNKNOWN;
    input->mouse_left = false;
    input->mouse_right = false;
    input->shift = false;
    input->ctrl = false;
    input->alt = false;
    input->esc = false;
    input->quit = false;
    if (input->mousePos)
        Position_destroy(input->mousePos);
    input->mousePos = NULL;*/

    SDL_Event evt;
    SDL_Scancode code;
    while (SDL_PollEvent(&evt)) {
        if (input->eventHandlers && Map_containsKey(input->eventHandlers, (void*)evt.type)) {
            List* handlers = Map_get(input->eventHandlers, (void*)evt.type);
            ListIterator* it = List_iterator(handlers);
            while (ListIterator_hasNext(it)) {
                void (*handler)(Input*, SDL_Event*) = ListIterator_next(it);
                if (handler) {
                    handler(input, &evt);
                }
            }
        }
        switch (evt.type) {
            case SDL_EVENT_QUIT:
                input->quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                if (input->keyEventHandlers && Map_containsKey(input->keyEventHandlers, (void*)evt.key.key)) {
                    List* handlers = Map_get(input->keyEventHandlers, (void*)evt.type);
                    ListIterator* it = List_iterator(handlers);
                    while (ListIterator_hasNext(it)) {
                        void (*handler)(Input*, SDL_Event*) = ListIterator_next(it);
                        if (handler) {
                            handler(input, &evt);
                        }
                    }
                }
                code = evt.key.key;
                input->lastPressed = code;
                List_push(input->keysDown, (void*)code);
                if (code == SDLK_LSHIFT || code == SDLK_RSHIFT) {
                    input->shift = true;
                } else if (code == SDLK_LCTRL || code == SDLK_RCTRL) {
                    input->ctrl = true;
                } else if (code == SDLK_LALT || code == SDLK_RALT) {
                    input->alt = true;
                }
                if (code == SDLK_ESCAPE) {
                    input->esc = true;
                }
                break;
            case SDL_EVENT_KEY_UP:
                code = evt.key.key;
                List_remove(input->keysDown, (void*)code);
                if (code == SDL_SCANCODE_LSHIFT || code == SDL_SCANCODE_RSHIFT) {
                    input->shift = false;
                } else if (code == SDL_SCANCODE_LCTRL || code == SDL_SCANCODE_RCTRL) {
                    input->ctrl = false;
                } else if (code == SDL_SCANCODE_LALT || code == SDL_SCANCODE_RALT) {
                    input->alt = false;
                }
                if (code == SDL_SCANCODE_ESCAPE) {
                    input->esc = false;
                }
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (evt.button.button == SDL_BUTTON_LEFT) {
                    input->mouse_left = true;
                } else if (evt.button.button == SDL_BUTTON_RIGHT) {
                    input->mouse_right = true;
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
                input->mousePos = Position_new(evt.motion.x, evt.motion.y);
                break;
            default:
                break;
        }
    }
}

bool Input_keyDown(Input* input, SDL_Scancode key) {
    return List_contains(input->keysDown, (void*)key);
}

bool Input_mouseInRect(Input* input, SDL_Rect rect) {
    if (!input) return false;
    Position* mouse = input->mousePos;
    return mouse->x >= rect.x &&
        mouse->x < rect.x + rect.w &&
        mouse->y >= rect.y &&
        mouse->y < rect.y + rect.h;
}

void Input_addKeyEventHandler(Input* input, SDL_Scancode key, void (*handler)(Input* input, SDL_Event* event)) {
    if (!input || !handler) return;
    if (!Map_containsKey(input->keyEventHandlers, (void*)key)) {
        List* handlers = List_create();
        List_push(handlers, (void*)handler);
        Map_put(input->keyEventHandlers, (void*)key, handlers);
    } else {
        List* handlers = Map_get(input->keyEventHandlers, (void*)key);
        List_push(handlers, (void*)handler);
    }
}

void Input_removeKeyEventHandler(Input* input, SDL_Scancode key) {
    if (!input) return;
    Map_remove(input->keyEventHandlers, (void*)key);
}

void Input_clearKeyEventHandlers(Input* input) {
    if (!input) return;
    Map_clear(input->keyEventHandlers);
}

void Input_addEventHandler(Input* input, Uint32 eventType, void (*handler)(Input* input, SDL_Event* event)) {
    if (!input || !handler) return;
    if (!Map_containsKey(input->eventHandlers, (void*)eventType)) {
        List* handlers = List_create();
        List_push(handlers, (void*)handler);
        Map_put(input->eventHandlers, (void*)eventType, handlers);
    } else {
        List* handlers = Map_get(input->eventHandlers, (void*)eventType);
        List_push(handlers, (void*)handler);
    }
}

void Input_removeEventHandler(Input* input, Uint32 eventType) {
    if (!input) return;
    Map_remove(input->eventHandlers, (void*)eventType);
}

void Input_clearEventHandlers(Input* input) {
    if (!input) return;
    Map_clear(input->eventHandlers);
}