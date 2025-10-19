/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct MainFrame {
    List* elements;
    App* app;
};

MainFrame* MainFrame_new(App* app);
void MainFrame_destroy(MainFrame* self);
void MainFrame_render(Frame* frame, SDL_Renderer* renderer, void* data);
void MainFrame_update(Frame* frame, void* data);
void MainFrame_focus(Frame* frame, void* data);
void MainFrame_unfocus(Frame* frame, void* data);