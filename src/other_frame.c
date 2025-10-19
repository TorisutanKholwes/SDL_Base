/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#include "other_frame.h"

#include "app.h"
#include "button.h"
#include "element.h"
#include "input_box.h"
#include "list.h"
#include "logger.h"
#include "style.h"
#include "text.h"
#include "utils.h"

static void OtherFrame_addElements(OtherFrame* self, App* app);
void OtherFrame_onButtonClick(Input* input, SDL_Event* evt, void* data);


OtherFrame* OtherFrame_new(App* app) {
    OtherFrame* self = calloc(1, sizeof(OtherFrame));
    if (!self) {
        error("Failed to allocate memory for MainFrame");
        return NULL;
    }

    self->app = app;
    self->elements = List_create();
    if (!self->elements) {
        error("Failed to create elements list for MainFrame");
        safe_free((void**)&self);
        return NULL;
    }
    OtherFrame_addElements(self, app);

    return self;
}

static void OtherFrame_addElements(OtherFrame* self, App* app) {
    Text* t = Text_new(
    app->renderer,
    "Hello World 2 !",
    TextStyle_default(app->manager),
    Position_new(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), true);
    Text_setColor(t, Color_rgb(0, 0, 0));
    List_push(self->elements, Element_fromText(t, NULL));

    Button* button = Button_new(
        app,
        "Click me 2 !",
        SDL_CreateRect(WINDOW_WIDTH / 2, 150, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT),
        ButtonStyle_default(app->manager), self);
    Button_onClick(button, OtherFrame_onButtonClick);
    List_push(self->elements, Element_fromButton(button, NULL));

    InputBox* inputBox = InputBox_new(app,
        SDL_CreateRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT),
        InputBoxStyle_default(app->manager), self);
    List_push(self->elements, Element_fromInput(inputBox, NULL));
}

void OtherFrame_destroy(OtherFrame* self) {
    if (!self) return;

    if (self->elements) {
        List_destroy(self->elements);
    }

    safe_free((void**)&self);
}

void OtherFrame_render(Frame* frame, SDL_Renderer* renderer, void* data) {
    OtherFrame* self = data;
    Element_renderList(self->elements, renderer);
}

void OtherFrame_update(Frame* frame, void* data) {
    OtherFrame* self = data;
    Element_updateList(self->elements);
}

void OtherFrame_focus(Frame* frame, void* data) {
    OtherFrame* self = data;
    Element_focusList(self->elements);
}

void OtherFrame_unfocus(Frame* frame, void* data) {
    OtherFrame* self = data;
    Element_unfocusList(self->elements);
}

void OtherFrame_onButtonClick(Input* input, SDL_Event* evt, void* data) {
    Button* button = data;
    if (button->parent) {
        OtherFrame* self = button->parent;
        App_frameBack(self->app);
    }
}