/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct SecondFrame {
    List* elements;
    App* app;
};

SecondFrame* SecondFrame_new(App* app);
void SecondFrame_destroy(SecondFrame* self);
void SecondFrame_render(Frame* frame, SDL_Renderer* renderer, void* data);
void SecondFrame_update(Frame* frame, void* data);
void SecondFrame_focus(Frame* frame, void* data);
void SecondFrame_unfocus(Frame* frame, void* data);