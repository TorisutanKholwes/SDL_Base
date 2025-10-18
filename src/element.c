/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "element.h"

#include "logger.h"
#include "button.h"
#include "text.h"

Element* Element_fromButton(Button* button) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromButton: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_BUTTON;
    element->data.button = button;
    return element;
}

Element* Element_fromText(Text* text) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_TEXT;
    element->data.text = text;
    return element;
}

void Element_destroy(Element* element) {
    if (!element) return;

    switch (element->type) {
        case ELEMENT_TYPE_BUTTON:
            Button_destroy(element->data.button);
            break;
        case ELEMENT_TYPE_TEXT:
            Text_destroy(element->data.text);
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_destroy: Unknown element type %d", element->type);
            break;
    }

    free(element);
}


void Element_render(Element* element, SDL_Renderer* renderer) {
    if (!element || !renderer) return;
    switch (element->type) {
        case ELEMENT_TYPE_BUTTON:
            Button_render(element->data.button, renderer);
            break;
        case ELEMENT_TYPE_TEXT:
            Text_render(element->data.text);
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_render: Unknown element type %d", element->type);
            break;
    }
}

void Element_update(Element* element) {
    if (!element) return;
    switch (element->type) {
        case ELEMENT_TYPE_BUTTON:
            Button_update(element->data.button);
            break;
        case ELEMENT_TYPE_TEXT:
            // No update needed for text currently
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_update: Unknown element type %d", element->type);
            break;
    }
}