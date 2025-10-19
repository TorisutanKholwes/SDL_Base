/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "main_frame.h"

#include "app.h"
#include "button.h"
#include "element.h"
#include "geometry.h"
#include "logger.h"
#include "list.h"
#include "other_frame.h"
#include "style.h"
#include "text.h"
#include "utils.h"
#include "frame.h"

static void MainFrame_addElements(MainFrame* self, App* app);
static void MainFrame_startAnimation(Input* input, SDL_Event* evt, void* data);

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
    Text* t = Text_new(
        app->renderer,
        "Hello World !",
        TextStyle_default(app->manager),
        Position_new(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), true);
    Text_setColor(t, Color_rgb(0, 0, 0));
    List_push(self->elements, Element_fromText(t, NULL));

    Box* box = Box_new(100.f, 100.f, 0, Position_new(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 + 150), Color_rgb(0, 0, 255), NULL);
    List_push(self->elements, Element_fromBox(box, NULL));

    Circle* circle = Circle_new(50, 0, Position_new(75, 75), Color_rgb(255, 0, 0), NULL);
    List_push(self->elements, Element_fromCircle(circle, NULL));

    Polygon* triangle = Polygon_newEmpty(Color_rgb(0, 255, 0));
    Polygon_addVertex(triangle, Position_new(200, 200));
    Polygon_addVertex(triangle, Position_new(250, 300));
    Polygon_addVertex(triangle, Position_new(150, 300));
    List_push(self->elements, Element_fromPolygon(triangle, NULL));

    Polygon* diamond = Polygon_newEmpty(Color_rgb(255, 255, 0));
    Polygon_addVertex(diamond, Position_new(400, 50));
    Polygon_addVertex(diamond, Position_new(450, 100));
    Polygon_addVertex(diamond, Position_new(400, 150));
    Polygon_addVertex(diamond, Position_new(350, 100));
    List_push(self->elements, Element_fromPolygon(diamond, NULL));

    Button* button = Button_new(
        app,
        "Test animation",
        SDL_CreateRect(WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 + 200, 250, 50),
        ButtonStyle_default(app->manager), self);
    List_push(self->elements, Element_fromButton(button, NULL));
    Button_onClick(button, MainFrame_startAnimation);
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

static void MainFrame_startAnimation(Input* _, SDL_Event* __, void* data) {
    Button* button = data;
    if (button->parent) {
        MainFrame* self = button->parent;
        OtherFrame* otherFrame = OtherFrame_new(self->app);
        if (otherFrame) {
            App_addFrame(self->app, Frame_new(otherFrame,
            OtherFrame_render, OtherFrame_update, OtherFrame_focus, OtherFrame_unfocus));
        }
    }
}
