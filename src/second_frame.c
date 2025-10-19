/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "second_frame.h"

#include "app.h"
#include "button.h"
#include "color.h"
#include "element.h"
#include "geometry.h"
#include "input.h"
#include "input_box.h"
#include "logger.h"
#include "list.h"
#include "style.h"
#include "utils.h"

static void SecondFrame_addElements(SecondFrame* self);
static void SecondFrame_onButtonClick(Input* input, SDL_Event* evt, void* data);

SecondFrame* SecondFrame_new(App* app) {
    SecondFrame* self = calloc(1, sizeof(SecondFrame));
    if (!self) {
        error("Failed to allocate memory for SecondFrame");
        return NULL;
    }
    self->elements = List_create();
    self->app = app;
    if (!self->elements) {
        error("Failed to create elements list for SecondFrame");
        safe_free((void**)&self);
        return NULL;
    }
    SecondFrame_addElements(self);

    return self;
}

static void SecondFrame_addElements(SecondFrame* self) {
    List_clear(self->elements);
    int w, h;
    SDL_GetWindowSize(self->app->window, &w, &h);

    Box* box = Box_new(w, h - 100, 0, Position_new(0, 0), COLOR_BLACK, NULL);
    List_push(self->elements, Element_fromBox(box, NULL));

    InputBox* input_box = InputBox_new(self->app,
        SDL_CreateRect(w / 4, h - 50, 200, 40),
        InputBoxStyle_default(self->app->manager),
        self);
    List_push(self->elements, Element_fromInput(input_box, "input"));

    Button* button = Button_new(self->app,
        Position_new(w / 2 + w / 4, h - 50),
        ButtonStyle_default(self->app->manager),
        self,
        "Append");
    Button_onClick(button, SecondFrame_onButtonClick);
    List_push(self->elements, Element_fromButton(button, NULL));
}

void SecondFrame_destroy(SecondFrame* self) {
    if (!self) return;

    if (self->elements) {
        List_destroy(self->elements);
    }

    safe_free((void**)&self);
}

void SecondFrame_render(Frame* _, SDL_Renderer* renderer, void* data) {
    SecondFrame* self = data;
    Element_renderList(self->elements, renderer);
}

void SecondFrame_update(Frame* _, void* data) {
    SecondFrame* self = data;
    Element_updateList(self->elements);

    if (self->app->input->esc) {
        App_frameBack(self->app);
    }
}

void SecondFrame_focus(Frame* _, void* data) {
    SecondFrame* self = data;
    Element_focusList(self->elements);
}

void SecondFrame_unfocus(Frame* _, void* data) {
    SecondFrame* self = data;
    Element_unfocusList(self->elements);
}

static void SecondFrame_onButtonClick(Input* input, SDL_Event* evt, void* data) {
    Button* button = data;
    if (button && button->parent) {
        SecondFrame* self = button->parent;
        InputBox* input_box = Element_getById(self->elements, "input")->data.inputbox;
        if (input_box) {
            log_message(LOG_LEVEL_DEBUG, "Input : %s; Is Number only : %d", InputBox_getString(input_box), String_isNumeric(InputBox_getString(input_box)));
        }
    }
}