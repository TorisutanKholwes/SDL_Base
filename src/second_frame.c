/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "second_frame.h"

#include "app.h"
#include "button.h"
#include "color.h"
#include "element.h"
#include "frame.h"
#include "geometry.h"
#include "input.h"
#include "input_box.h"
#include "logger.h"
#include "list.h"
#include "resource_manager.h"
#include "style.h"
#include "text.h"
#include "timer.h"
#include "utils.h"

static void SecondFrame_addElements(SecondFrame* self);
static void SecondFrame_onButtonClick(Input* input, SDL_Event* evt, void* data);
static void SecondFrame_onRuneB(Input* input, SDL_Event* evt, void* data);
static void SecondFrame_onRuneQ(Input* input, SDL_Event* evt, void* data);
static void SecondFrame_onRuneM(Input* input, SDL_Event* evt, void* data);

SecondFrame* SecondFrame_new(App* app) {
    SecondFrame* self = calloc(1, sizeof(SecondFrame));
    if (!self) {
        error("Failed to allocate memory for SecondFrame");
        return NULL;
    }
    self->elements = List_create();
    self->numbers = List_create();
    self->timer = Timer_new();
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
    ListIterator* it = ListIterator_new(self->elements);
    while (ListIterator_hasNext(it)) {
        Element* element = ListIterator_next(it);
        Element_destroy(element);
    }
    ListIterator_destroy(it);
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
        Position_new(w / 2, h - 50),
        ButtonStyle_default(self->app->manager),
        self,
        "Append");
    Button_onClick(button, SecondFrame_onButtonClick);
    List_push(self->elements, Element_fromButton(button, NULL));

    Text* text = Text_new(self->app->renderer, TextStyle_new(ResourceManager_getDefaultBoldFont(self->app->manager, 24),
        24, COLOR_WHITE, TTF_STYLE_NORMAL), Position_new(w / 2 + w / 4, h - 50), true, "Time take :");
    List_push(self->elements, Element_fromText(text, "Time"));

}

void SecondFrame_destroy(SecondFrame* self) {
    if (!self) return;

    if (self->elements) {
        ListIterator* it = ListIterator_new(self->elements);
        while (ListIterator_hasNext(it)) {
            Element* element = ListIterator_next(it);
            Element_destroy(element);
        }
        ListIterator_destroy(it);
        List_destroy(self->elements);
    }

    if (self->numbers) {
        List_destroy(self->numbers);
    }

    if (self->timer) {
        Timer_destroy(self->timer);
    }

    safe_free((void**)&self);
}

void SecondFrame_render(Frame* _, SDL_Renderer* renderer, void* data) {
    SecondFrame* self = data;
    Element_renderList(self->elements, renderer);
    int w, h;
    SDL_GetWindowSize(self->app->window, &w, &h);

    ListIterator* it = ListIterator_new(self->numbers);
    while (ListIterator_hasNext(it)) {
        int num = (int) ListIterator_next(it);
        Text* text = Text_newf(self->app->renderer, TextStyle_new(ResourceManager_getDefaultBoldFont(self->app->manager, 32),
            32, COLOR_WHITE, TTF_STYLE_NORMAL),
            Position_new(55 * it->index, h - 150), true, "%d", num);
        Text_render(text);

        Box* box = Box_new(50, num, 0, Position_new(55 * it->index, h - 150 - (Text_getSize(text).height / 2) - (num / 2)), COLOR_BLUE, NULL);
        Box_render(box, renderer);

        Text_destroy(text);
        Box_destroy(box);
    }
    ListIterator_destroy(it);

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

    Input_addKeyEventHandler(self->app->input, SDLK_B, SecondFrame_onRuneB, self);
    Input_addKeyEventHandler(self->app->input, SDLK_Q, SecondFrame_onRuneQ, self);
    Input_addKeyEventHandler(self->app->input, SDLK_M, SecondFrame_onRuneM, self);
}

void SecondFrame_unfocus(Frame* _, void* data) {
    SecondFrame* self = data;
    Element_unfocusList(self->elements);

    Input_removeOneKeyEventHandler(self->app->input, SDLK_B, self);
    Input_removeOneKeyEventHandler(self->app->input, SDLK_Q, self);
    Input_removeOneKeyEventHandler(self->app->input, SDLK_M, self);
}

static void SecondFrame_onButtonClick(Input* input, SDL_Event* evt, void* data) {
    Button* button = data;
    if (button && button->parent) {
        SecondFrame* self = button->parent;
        InputBox* input_box = Element_getById(self->elements, "input")->data.inputbox;
        if (input_box) {
            char* str = InputBox_getString(input_box);
            if (!String_isNumeric(str)) {
                log_message(LOG_LEVEL_WARN, "Input is not a valid number: %s", str);
                return;
            }
            int num = String_parseInt(str, 0);
            if (num > 400) {
                return;
            }
            List_push_int(self->numbers, (long)num);
            InputBox_setString(input_box, "");
        }
    }
}

Frame* SecondFrame_getFrame(SecondFrame* self) {
    Frame* frame = Frame_new(self, SecondFrame_render, SecondFrame_update, SecondFrame_focus, SecondFrame_unfocus, (DestroyFunc) SecondFrame_destroy);
    Frame_setTitle(frame, "SecondFrame");
    return frame;
}

static void SecondFrame_onRuneB(Input* input, SDL_Event* evt, void* data) {
    SecondFrame *self = data;
    if (!self) {
        return;
    }
    Timer_start(self->timer);
    List_sort(self->numbers, LIST_SORT_TYPE_BUBBLE);
    Uint32 elapsed = Timer_getTicks(self->timer);
    Timer_stop(self->timer);
    Text* text = Element_getById(self->elements, "Time")->data.text;
    Text_setStringf(text, "Time take : %u ms", elapsed);
}

static void SecondFrame_onRuneQ(Input* input, SDL_Event* evt, void* data) {
    SecondFrame *self = data;
    if (!self) {
        return;
    }
    Timer_start(self->timer);
    List_sort(self->numbers, LIST_SORT_TYPE_QUICK);
    Uint32 elapsed = Timer_getTicks(self->timer);
    Timer_stop(self->timer);
    Text* text = Element_getById(self->elements, "Time")->data.text;
    Text_setStringf(text, "Time take : %u ms", elapsed);
}

static void SecondFrame_onRuneM(Input* input, SDL_Event* evt, void* data) {
    SecondFrame *self = data;
    if (!self) {
        return;
    }
    Timer_start(self->timer);
    List_sort(self->numbers, LIST_SORT_TYPE_MERGE);
    Uint32 elapsed = Timer_getTicks(self->timer);
    Timer_stop(self->timer);
    Text* text = Element_getById(self->elements, "Time")->data.text;
    Text_setStringf(text, "Time take : %u ms", elapsed);
}