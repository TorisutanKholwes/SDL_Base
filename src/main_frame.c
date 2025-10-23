/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "main_frame.h"

#include "app.h"
#include "button.h"
#include "color.h"
#include "element.h"
#include "frame.h"
#include "geometry.h"
#include "input.h"
#include "layout_test_frame.h"
#include "logger.h"
#include "list.h"
#include "resource_manager.h"
#include "second_frame.h"
#include "style.h"
#include "utils.h"
#include "text.h"

static void MainFrame_addElements(MainFrame* self, App* app);
static void MainFrame_goToNextPage(Input* input, SDL_Event* evt, void* data);
static void MainFrame_onWindowResized(Input* input, SDL_Event* evt, void* data);
static void MainFrame_onRuneN(Input* input, SDL_Event* evt, void* data);

MainFrame* MainFrame_new(App* app) {
    MainFrame* self = calloc(1, sizeof(MainFrame));
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
    MainFrame_addElements(self, app);

    return self;
}

static void MainFrame_addElements(MainFrame* self, App* app) {
    ListIterator* it = ListIterator_new(self->elements);
    while (ListIterator_hasNext(it)) {
        Element* element = ListIterator_next(it);
        Element_destroy(element);
    }
    ListIterator_destroy(it);
    List_clear(self->elements);
    int w, h;
    SDL_GetWindowSize(app->window, &w, &h);

    Text* title = Text_newf(app->renderer,
        TextStyle_new(ResourceManager_getDefaultBoldFont(app->manager, 40),
            40,
            COLOR_WHITE,
            TTF_STYLE_NORMAL),
            Position_new(w / 2, 100), true,
            "Welcome to %s!", APP_NAME);
    List_push(self->elements, Element_fromText(title, NULL));

    Polygon* octagon = Polygon_newEmpty(0, COLOR_YELLOW, NULL);
    for (int i = 0; i < 8; i++) {
        int octagon_size = 100;
        Polygon_addVertex(octagon,
                          Position_new(
                              w / 2 + octagon_size * cos(i * M_PI / 4),
                              h / 2 + octagon_size * sin(i * M_PI / 4)
                          )
        );
    }
    List_push(self->elements, Element_fromPolygon(octagon, NULL));

    Button* button = Button_new(app,
        Position_new(w / 2, h / 2 + 200),
        ButtonStyle_new(FullStyleColors_new(COLOR_WHITE, COLOR_GRAY(150), COLOR_BLACK),
            2,
            ResourceManager_getDefaultFont(app->manager, 24),
            TTF_STYLE_NORMAL,
            24,
            EdgeInsets_newSymmetric(10, 20)),
        self,
        "Go to next page");
    Button_onClick(button, MainFrame_goToNextPage);
    List_push(self->elements, Element_fromButton(button, NULL));
}

void MainFrame_destroy(MainFrame* self) {
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

    safe_free((void**)&self);
}

void MainFrame_render(SDL_Renderer* renderer, MainFrame* self) {
    Element_renderList(self->elements, renderer);
}

void MainFrame_update(MainFrame* self) {
    Element_updateList(self->elements);
}

void MainFrame_focus(MainFrame* self) {
    Element_focusList(self->elements);

    Input_addEventHandler(self->app->input, SDL_EVENT_WINDOW_RESIZED, MainFrame_onWindowResized, self);
    Input_addKeyEventHandler(self->app->input, SDLK_N, MainFrame_onRuneN, self);
}

void MainFrame_unfocus(MainFrame* self) {
    Element_unfocusList(self->elements);

    Input_removeOneEventHandler(self->app->input, SDL_EVENT_WINDOW_RESIZED, self);
    Input_removeOneKeyEventHandler(self->app->input, SDLK_N, self);
}

Frame* MainFrame_getFrame(MainFrame* self) {
    Frame* frame = Frame_new(self,
        (FrameRenderFunc) MainFrame_render,
        (FrameUpdateFunc) MainFrame_update,
        (FrameFocusFunc) MainFrame_focus,
        (FrameFocusFunc) MainFrame_unfocus,
        (DestroyFunc) MainFrame_destroy);
    Frame_setTitle(frame, "MainFrame");
    return frame;
}

static void MainFrame_goToNextPage(Input* input, SDL_Event* evt, void* data) {
    Button* button = data;
    if (button && button->parent) {
        MainFrame* self = button->parent;
        SecondFrame* second = SecondFrame_new(self->app);
        App_addFrame(self->app, SecondFrame_getFrame(second));
    }
}

static void MainFrame_onWindowResized(Input* input, SDL_Event* evt, void* data) {
    MainFrame* self = data;
    MainFrame_addElements(self, self->app);
}

static void MainFrame_onRuneN(Input* input, SDL_Event* evt, void* data) {
    MainFrame* self = data;
    App_addFrame(self->app, LayoutTestFrame_getFrame(LayoutTestFrame_new(self->app)));
}