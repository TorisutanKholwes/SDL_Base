/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

enum ElementType {
    ELEMENT_TYPE_BUTTON,
    ELEMENT_TYPE_TEXT,
    ELEMENT_TYPE_INPUT,

    ELEMENT_TYPE_BOX,
    ELEMENT_TYPE_CIRCLE,
    ELEMENT_TYPE_POLYGON
};

struct Element {
    ElementType type;
    char* id;
    union {
        Button* button;
        Text* text;
        InputBox* inputbox;
        Box* box;
        Circle* circle;
        Polygon* polygon;
    } data;
};

Element* Element_fromButton(Button* button, const char* id);
Element* Element_fromText(Text* text, const char* id);
Element* Element_fromInput(InputBox* input, const char* id);
Element* Element_fromBox(Box* box, const char* id);
Element* Element_fromCircle(Circle* circle, const char* id);
Element* Element_fromPolygon(Polygon* polygon, const char* id);

void Element_destroy(Element* element);

void Element_render(Element* element, SDL_Renderer* renderer);
void Element_update(Element* element);
void Element_focus(Element* element);
void Element_unfocus(Element* element);

void Element_renderList(List* list, SDL_Renderer* renderer);
void Element_updateList(List* list);
void Element_focusList(List* list);
void Element_unfocusList(List* list);

Element* Element_getById(List* list, const char* id);

char* ElementType_toString(ElementType type);