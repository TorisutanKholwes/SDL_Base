/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct OtherFrame {
    List* elements;
    App* app;
};

OtherFrame* OtherFrame_new(App* app);
void OtherFrame_destroy(OtherFrame* self);
void OtherFrame_render(Frame* frame, SDL_Renderer* renderer, void* data);
void OtherFrame_update(Frame* frame, void* data);
void OtherFrame_focus(Frame* frame, void* data);
void OtherFrame_unfocus(Frame* frame, void* data);