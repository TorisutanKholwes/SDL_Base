/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "layout_test_frame.h"

#include "app.h"
#include "button.h"
#include "color.h"
#include "element.h"
#include "frame.h"
#include "geometry.h"
#include "input.h"
#include "input_box.h"
#include "layout.h"
#include "list.h"
#include "logger.h"
#include "resource_manager.h"
#include "style.h"
#include "text.h"
#include "utils.h"

static void LayoutTestFrame_addElements(LayoutTestFrame* self);

LayoutTestFrame* LayoutTestFrame_new(App* app) {
    LayoutTestFrame* self = calloc(1, sizeof(LayoutTestFrame));
    if (!self) {
        error("Failed to allocate memory for LayoutTestFrame");
        return NULL;
    }
    self->app = app;
    self->elements = List_create();
    if (!self->elements) {
        error("Failed to allocate memory for LayoutTestFrame->elements");
        safe_free((void**)&self);;
        return NULL;
    }
    self->rowContainer = NULL;
    self->columnContainer = NULL;
    LayoutTestFrame_addElements(self);

    return self;
}

void LayoutTestFrame_destroy(LayoutTestFrame* self) {
    if (!self) return;

    if (self->elements) {
        List_destroyWitValues(self->elements, (DestroyFunc)Element_destroy);
    }

    if (self->rowContainer) {
        FlexContainer_destroy(self->rowContainer);
    }

    if (self->columnContainer) {
        FlexContainer_destroy(self->columnContainer);
    }

    safe_free((void**)&self);
}

void LayoutTestFrame_render(Frame* frame, SDL_Renderer* renderer, LayoutTestFrame* self) {
    Element_renderList(self->elements, renderer);
}

void LayoutTestFrame_update(Frame* frame, LayoutTestFrame* self) {
    Element_updateList(self->elements);

    if (self->app->input->esc) {
        App_frameBack(self->app);
    }
}

void LayoutTestFrame_focus(Frame* frame, LayoutTestFrame* self) {
    Element_focusList(self->elements);
}

void LayoutTestFrame_unfocus(Frame* frame, LayoutTestFrame* self) {
    Element_unfocusList(self->elements);
}

Frame* LayoutTestFrame_getFrame(LayoutTestFrame* self) {
    Frame* frame = Frame_new(self, (FrameRenderFunc)LayoutTestFrame_render,
        (FrameUpdateFunc)LayoutTestFrame_update,
        (FrameFocusFunc)LayoutTestFrame_focus,
        (FrameFocusFunc) LayoutTestFrame_unfocus,
        (DestroyFunc) LayoutTestFrame_destroy);
    Frame_setTitle(frame, "LayoutTestFrame");
    return frame;
}

static void LayoutTestFrame_addElements(LayoutTestFrame* self) {
    int w, h;
    SDL_GetWindowSize(self->app->window, &w, &h);

    Box* box = Box_new(w, h/2, 0, Position_new(0, 0), COLOR_RED, NULL, false);
    Element* boxElement = Element_fromBox(box, NULL);
    List_push(self->elements, boxElement);

    self->rowContainer = FlexContainer_new(0, 0, w, h/2);
    FlexContainer_setDirection(self->rowContainer, FLEX_DIRECTION_ROW);
    FlexContainer_setAlignItems(self->rowContainer, FLEX_ALIGN_CENTER);
    FlexContainer_setGap(self->rowContainer, 20);

    Button* btn = Button_new(self->app, POSITION_NULL, ButtonStyle_new(FullStyleColors_new(COLOR_WHITE, COLOR_GRAY(100), COLOR_BLACK),
        2,
        ResourceManager_getDefaultFont(self->app->manager, 20),
        TTF_STYLE_NORMAL,
        20,
        //EdgeInsets_zero()
        EdgeInsets_newSymmetric(8, 15)
        ), self, "Button");
    Element* elt1 = Element_fromButton(btn, NULL);
    FlexContainer_addElement(self->rowContainer, elt1, 1.f, 1.f, -1.f);
    List_push(self->elements, elt1);

    InputBox* input = InputBox_new(self->app, SDL_CreateRect(-1, -1, -1, 40), InputBoxStyle_new(
        ResourceManager_getDefaultFont(self->app->manager, 20),
        20,
        TTF_STYLE_NORMAL,
        FullStyleColors_new(COLOR_WHITE, COLOR_GRAY(100), COLOR_BLACK)
        ), self);
    Element* elt2 = Element_fromInput(input, NULL);
    FlexContainer_addElement(self->rowContainer, elt2, 1.f, 0.f, -1.f);
    List_push(self->elements, elt2);

    Text* text = Text_new(self->app->renderer, TextStyle_new(
        ResourceManager_getDefaultBoldFont(self->app->manager, 20),
        20,
        COLOR_WHITE,
        TTF_STYLE_NORMAL), POSITION_NULL, false, "Text element");
    Element* elt3 = Element_fromText(text, NULL);
    FlexContainer_addElement(self->rowContainer, elt3, 1.f, 1.f, -1.f);
    List_push(self->elements, elt3);

    FlexContainer_layout(self->rowContainer);

    Box* box2 = Box_new(w, h/2, 0, Position_new(0, h/2), COLOR_GREEN, NULL, false);
    Element* boxElement2 = Element_fromBox(box2, NULL);
    List_push(self->elements, boxElement2);

    self->columnContainer = FlexContainer_new(0, h/2, w, h/2);
    FlexContainer_setDirection(self->columnContainer, FLEX_DIRECTION_COLUMN);
    FlexContainer_setAlignItems(self->columnContainer, FLEX_ALIGN_CENTER);
    FlexContainer_setGap(self->columnContainer, 20);
    Button* btn2 = Button_new(self->app, POSITION_NULL, ButtonStyle_new(FullStyleColors_new(COLOR_WHITE, COLOR_GRAY(100), COLOR_BLACK),
        2,
        ResourceManager_getDefaultFont(self->app->manager, 20),
        TTF_STYLE_NORMAL,
        20,
        //EdgeInsets_zero()
        EdgeInsets_newSymmetric(8, 15)
        ), self, "Button");
    Element* elt4 = Element_fromButton(btn2, NULL);
    FlexContainer_addElement(self->columnContainer, elt4, 1.f, 1.f, -1.f);
    List_push(self->elements, elt4);
    InputBox* input2 = InputBox_new(self->app, SDL_CreateRect(-1, -1, w/2, 40), InputBoxStyle_new(
        ResourceManager_getDefaultFont(self->app->manager, 20),
        20,
        TTF_STYLE_NORMAL,
        FullStyleColors_new(COLOR_WHITE, COLOR_GRAY(100), COLOR_BLACK)
        ), self);
    Element* elt5 = Element_fromInput(input2, NULL);
    FlexContainer_addElement(self->columnContainer, elt5, 1.f, 0.f, -1.f);
    List_push(self->elements, elt5);
    Text* text2 = Text_new(self->app->renderer, TextStyle_new(
        ResourceManager_getDefaultBoldFont(self->app->manager, 20),
        20,
        COLOR_WHITE,
        TTF_STYLE_NORMAL), POSITION_NULL, false, "Text element");
    Element* elt6 = Element_fromText(text2, NULL);
    FlexContainer_addElement(self->columnContainer, elt6, 1.f, 1.f, -1.f);
    List_push(self->elements, elt6);
    FlexContainer_layout(self->columnContainer);
}
