/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "element.h"

#include "logger.h"
#include "button.h"
#include "geometry.h"
#include "image.h"
#include "input_box.h"
#include "list.h"
#include "text.h"
#include "utils.h"

Element* Element_fromButton(Button* button, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromButton: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_BUTTON;
    element->id = Strdup(id);
    element->data.button = button;
    return element;
}

Element* Element_fromText(Text* text, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_TEXT;
    element->id = Strdup(id);
    element->data.text = text;
    return element;
}

Element* Element_fromInput(InputBox* input, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromInput: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_INPUT;
    element->id = Strdup(id);
    element->data.input_box = input;
    return element;
}

Element* Element_fromBox(Box* box, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_BOX;
    element->id = Strdup(id);
    element->data.box = box;
    return element;
}

Element* Element_fromCircle(Circle* circle, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_CIRCLE;
    element->id = Strdup(id);
    element->data.circle = circle;
    return element;
}

Element* Element_fromPolygon(Polygon* polygon, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_POLYGON;
    element->id = Strdup(id);
    element->data.polygon = polygon;
    return element;
}

Element* Element_fromImage(Image* image, const char* id) {
    Element* element = calloc(1, sizeof(Element));
    if (!element) {
        error("Element_fromText: Failed to allocate memory for Element");
        return NULL;
    }
    element->type = ELEMENT_TYPE_IMAGE;
    element->id = Strdup(id);
    element->data.image = image;
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
        case ELEMENT_TYPE_BOX:
            Box_destroy(element->data.box);
            break;
        case ELEMENT_TYPE_CIRCLE:
            Circle_destroy(element->data.circle);
            break;
        case ELEMENT_TYPE_POLYGON:
            Polygon_destroy(element->data.polygon);
            break;
        case ELEMENT_TYPE_INPUT:
            InputBox_destroy(element->data.input_box);
            break;
        case ELEMENT_TYPE_IMAGE:
            Image_destroy(element->data.image);
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_destroy: Unknown element type %d", element->type);
            break;
    }

    safe_free((void**)&element->id);
    safe_free((void**)&element);
}

void Element_destroyList(List* list) {
    if (!list) return;
    List_destroyWitValues(list, (DestroyFunc) Element_destroy);
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
        case ELEMENT_TYPE_BOX:
            Box_render(element->data.box, renderer);
            break;
        case ELEMENT_TYPE_CIRCLE:
            Circle_render(element->data.circle, renderer);
            break;
        case ELEMENT_TYPE_POLYGON:
            Polygon_render(element->data.polygon, renderer);
            break;
        case ELEMENT_TYPE_INPUT:
            InputBox_render(element->data.input_box, renderer);
            break;
        case ELEMENT_TYPE_IMAGE:
            Image_render(element->data.image, renderer);
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
        case ELEMENT_TYPE_INPUT:
            InputBox_update(element->data.input_box);
            break;
        case ELEMENT_TYPE_TEXT:
        case ELEMENT_TYPE_BOX:
        case ELEMENT_TYPE_CIRCLE:
        case ELEMENT_TYPE_POLYGON:
        case ELEMENT_TYPE_IMAGE:
            // No update needed for text currently
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_update: Unknown element type %d", element->type);
            break;
    }
}

void Element_focus(Element* element) {
    if (!element) return;
    switch (element->type) {
        case ELEMENT_TYPE_BUTTON:
            Button_focus(element->data.button);
            break;
        case ELEMENT_TYPE_INPUT:
            InputBox_focus(element->data.input_box);
            break;
        case ELEMENT_TYPE_TEXT:
        case ELEMENT_TYPE_BOX:
        case ELEMENT_TYPE_CIRCLE:
        case ELEMENT_TYPE_POLYGON:
        case ELEMENT_TYPE_IMAGE:
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_focus: Unknown element type %d", element->type);
            break;
    }
}

void Element_unfocus(Element* element) {
    if (!element) return;
    switch (element->type) {
        case ELEMENT_TYPE_BUTTON:
            Button_unFocus(element->data.button);
            break;
        case ELEMENT_TYPE_INPUT:
            InputBox_unFocus(element->data.input_box);
            break;
        case ELEMENT_TYPE_TEXT:
        case ELEMENT_TYPE_BOX:
        case ELEMENT_TYPE_CIRCLE:
        case ELEMENT_TYPE_POLYGON:
        case ELEMENT_TYPE_IMAGE:
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Element_unfocus: Unknown element type %d", element->type);
            break;
    }
}


void Element_renderList(List* list, SDL_Renderer* renderer) {
    ListIterator* iterator = ListIterator_new(list);
    while (ListIterator_hasNext(iterator)) {
        Element* element = ListIterator_next(iterator);
        Element_render(element, renderer);
    }
    ListIterator_destroy(iterator);
}

void Element_updateList(List* list) {
    ListIterator* iterator = ListIterator_new(list);
    while (ListIterator_hasNext(iterator)) {
        Element* element = ListIterator_next(iterator);
        Element_update(element);
    }
    ListIterator_destroy(iterator);
}

void Element_focusList(List* list) {
    ListIterator* iterator = ListIterator_new(list);
    while (ListIterator_hasNext(iterator)) {
        Element* element = ListIterator_next(iterator);
        Element_focus(element);
    }
    ListIterator_destroy(iterator);
}

void Element_unfocusList(List* list) {
    ListIterator* iterator = ListIterator_new(list);
    while (ListIterator_hasNext(iterator)) {
        Element* element = ListIterator_next(iterator);
        Element_unfocus(element);
    }
    ListIterator_destroy(iterator);
}

Element* Element_getById(List* list, const char* id) {
    ListIterator* iterator = ListIterator_new(list);
    while (ListIterator_hasNext(iterator)) {
        Element* element = ListIterator_next(iterator);
        if (String_equals(element->id, id)) {
            ListIterator_destroy(iterator);
            return element;
        }
    }
    ListIterator_destroy(iterator);
    return NULL;
}

char* ElementType_toString(ElementType type) {
    switch (type) {
        case ELEMENT_TYPE_BUTTON:
            return "BUTTON";
        case ELEMENT_TYPE_TEXT:
            return "TEXT";
        case ELEMENT_TYPE_INPUT:
            return "INPUT";
        case ELEMENT_TYPE_BOX:
            return "BOX";
        case ELEMENT_TYPE_CIRCLE:
            return "CIRCLE";
        case ELEMENT_TYPE_POLYGON:
            return "POLYGON";
        case ELEMENT_TYPE_IMAGE:
            return "IMAGE";
        default:
            return "UNKNOWN";
    }
}