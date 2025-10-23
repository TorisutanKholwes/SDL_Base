/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct SecondFrame {
    List* elements;
    App* app;
    List* numbers;
    Timer* timer;
};

SecondFrame* SecondFrame_new(App* app);
void SecondFrame_destroy(SecondFrame* self);
void SecondFrame_render(SDL_Renderer* renderer, SecondFrame* self);
void SecondFrame_update(SecondFrame* self);
void SecondFrame_focus(SecondFrame* self);
void SecondFrame_unfocus(SecondFrame* self);

Frame* SecondFrame_getFrame(SecondFrame* self);