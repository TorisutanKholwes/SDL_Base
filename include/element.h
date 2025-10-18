/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

enum ElementType {
    ELEMENT_TYPE_BUTTON,
    ELEMENT_TYPE_TEXT,
};

struct Element {
    ElementType type;
    union {
        Button* button;
        Text* text;
    } data;
};

Element* Element_fromButton(Button* button);
Element* Element_fromText(Text* text);
void Element_destroy(Element* element);

void Element_render(Element* element, SDL_Renderer* renderer);
void Element_update(Element* element);