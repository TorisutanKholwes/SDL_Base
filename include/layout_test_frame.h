/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#pragma once

#include "Settings.h"

struct LayoutTestFrame {
    App* app;
    List* elements;
    FlexContainer* rowContainer;
    FlexContainer* columnContainer;
};

LayoutTestFrame* LayoutTestFrame_new(App* app);
void LayoutTestFrame_destroy(LayoutTestFrame* self);
void LayoutTestFrame_render(Frame* frame, SDL_Renderer* renderer, LayoutTestFrame* self);
void LayoutTestFrame_update(Frame* frame, LayoutTestFrame* self);
void LayoutTestFrame_focus(Frame* frame, LayoutTestFrame* self);
void LayoutTestFrame_unfocus(Frame* frame, LayoutTestFrame* self);

Frame* LayoutTestFrame_getFrame(LayoutTestFrame* self);