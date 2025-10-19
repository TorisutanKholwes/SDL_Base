/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "main_frame.h"

#include "app.h"
#include "button.h"
#include "color.h"
#include "element.h"
#include "geometry.h"
#include "logger.h"
#include "list.h"
#include "resource_manager.h"
#include "style.h"
#include "utils.h"
#include "text.h"

static void MainFrame_addElements(MainFrame* self, App* app);
static void MainFrame_goToNextPage(Input* input, SDL_Event* evt, void* data);

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
        List_destroy(self->elements);
    }

    safe_free((void**)&self);
}

void MainFrame_render(Frame* _, SDL_Renderer* renderer, void* data) {
    MainFrame* self = data;
    Element_renderList(self->elements, renderer);
}

void MainFrame_update(Frame* _, void* data) {
    MainFrame* self = data;
    Element_updateList(self->elements);
}

void MainFrame_focus(Frame* _, void* data) {
    MainFrame* self = data;
    Element_focusList(self->elements);
}

void MainFrame_unfocus(Frame* _, void* data) {
    MainFrame* self = data;
    Element_unfocusList(self->elements);
}

static void MainFrame_goToNextPage(Input* input, SDL_Event* evt, void* data) {
    log_message(LOG_LEVEL_DEBUG, "TODO : Go to next page");
}