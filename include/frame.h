/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Frame {
    void* element;
    FrameRenderFunc func_render;
    FrameUpdateFunc func_update;
    FrameFocusFunc func_focus;
    FrameFocusFunc func_unfocus;
};

Frame* Frame_new(void* element, FrameRenderFunc func_render,FrameUpdateFunc func_update, FrameFocusFunc func_focus, FrameFocusFunc func_unfocus);
void Frame_destroy(Frame* frame);
void Frame_render(Frame* frame, SDL_Renderer* renderer);
void Frame_update(Frame* frame);