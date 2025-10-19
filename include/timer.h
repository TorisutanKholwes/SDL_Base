/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Timer {
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool paused;
    bool started;
};

Timer* Timer_new();
void Timer_destroy(Timer* self);
void Timer_start(Timer* self);
void Timer_stop(Timer* self);
void Timer_reset(Timer* self);
void Timer_pause(Timer* self);
void Timer_resume(Timer* self);
Uint32 Timer_getTicks(Timer* self);
