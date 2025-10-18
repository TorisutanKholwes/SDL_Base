/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct Frame {
    void* element;
    FrameUpdateFunc func_update;
    FrameRenderFunc func_render;
};

Frame* Frame_new(void* element, FrameUpdateFunc func_update, FrameRenderFunc func_render);
void Frame_destroy(Frame* frame);
void Frame_render(Frame* frame, SDL_Renderer* renderer);
void Frame_update(Frame* frame);