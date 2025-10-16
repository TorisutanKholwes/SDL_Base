/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "app.h"

typedef struct {
    int x, y;
} Position;

Position* Position_new(int x, int y);
void Position_destroy(Position* pos);

void safe_free(void** ptr);
void quit_sdl(const App *app);