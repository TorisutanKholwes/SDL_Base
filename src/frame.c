/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "frame.h"
#include "logger.h"
#include "utils.h"

Frame* Frame_new(void* element, FrameRenderFunc func_render,FrameUpdateFunc func_update, FrameFocusFunc func_focus, FrameFocusFunc func_unfocus, DestroyFunc func_destroy) {
    Frame* frame = calloc(1, sizeof(Frame));
    if (!frame) {
        error("Frame_new: failed to allocate memory for Frame");
        return NULL;
    }

    frame->element = element;
    frame->func_update = func_update;
    frame->func_render = func_render;
    frame->func_focus = func_focus;
    frame->func_unfocus = func_unfocus;
    frame->func_destroy = func_destroy;
    frame->title = NULL;

    return frame;
}

void Frame_destroy(Frame* frame) {
    if (!frame) return;
    if (frame->func_destroy && frame->element) {
        frame->func_destroy(frame->element);
    }
    safe_free((void**)&frame);
}

void Frame_render(Frame* frame, SDL_Renderer* renderer) {
    if (!frame || !frame->func_render) return;
    frame->func_render(renderer, frame->element);
}

void Frame_update(Frame* frame) {
    if (!frame || !frame->func_update) return;
    frame->func_update(frame->element);
}

void Frame_setTitle(Frame* frame, const char* title) {
    if (!frame) return;
    safe_free((void**)&frame->title);
    if (title) {
        frame->title = Strdup(title);
    }
}