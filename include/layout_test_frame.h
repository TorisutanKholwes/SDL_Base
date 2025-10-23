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
void LayoutTestFrame_render(SDL_Renderer* renderer, LayoutTestFrame* self);
void LayoutTestFrame_update(LayoutTestFrame* self);
void LayoutTestFrame_focus(LayoutTestFrame* self);
void LayoutTestFrame_unfocus(LayoutTestFrame* self);

Frame* LayoutTestFrame_getFrame(LayoutTestFrame* self);