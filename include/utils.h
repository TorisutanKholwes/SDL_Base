/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Position {
    int x, y;
};

Position* Position_new(int x, int y);
void Position_destroy(Position* pos);

void safe_free(void** ptr);
void quit_sdl(const App *app);