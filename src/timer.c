/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#include "timer.h"

#include "logger.h"
#include "utils.h"

Timer* Timer_new() {
    Timer* self = calloc(1, sizeof(Timer));
    if (!self) {
        error("Failed to allocate memory for Timer");
        return NULL;
    }
    self->started = false;
    self->paused = false;
    self->startTicks = 0;
    self->pausedTicks = 0;
    return self;
}

void Timer_destroy(Timer* self) {
    if (!self) return;
    safe_free((void**)&self);
}

void Timer_start(Timer* self) {
    self->started = true;
    self->paused = false;
    self->startTicks = SDL_GetTicks();
    self->pausedTicks = 0;
}

void Timer_stop(Timer* self) {
    self->started = false;
    self->paused = false;
    self->startTicks = 0;
    self->pausedTicks = 0;
}

void Timer_reset(Timer* self) {
    self->paused = false;
    self->started = true;
    self->startTicks = SDL_GetTicks();
    self->pausedTicks = 0;
}

void Timer_pause(Timer* self) {
    if (self->started && !self->paused) {
        self->paused = true;
        self->pausedTicks = SDL_GetTicks() - self->startTicks;
    }
}

void Timer_resume(Timer* self) {
    if (self->started && self->paused) {
        self->paused = false;
        self->startTicks = SDL_GetTicks() - self->pausedTicks;
        self->pausedTicks = 0;
    }
}

Uint32 Timer_getTicks(Timer* self) {
    if (self->started) {
        if (self->paused) {
            return self->pausedTicks;
        } else {
            return SDL_GetTicks() - self->startTicks;
        }
    }
    return 0;
}