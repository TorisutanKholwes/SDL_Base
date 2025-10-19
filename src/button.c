/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "button.h"

#include "logger.h"
#include "utils.h"
#include "text.h"
#include "app.h"
#include "input.h"
#include "style.h"

static void Button_checkHover(Input* input, SDL_Event* evt, void* buttonData);
static void Button_checkPressed(Input* input, SDL_Event* evt, void* buttonData);

Button* Button_new(const App* app, const char* label, SDL_FRect rect, ButtonStyle* style, void* parent) {
    Button* button = calloc(1, sizeof(Button));
    if (!button) {
        error("Failed to allocate memory for Button");
        return NULL;
    }
    button->text = Text_new(app->renderer, label, TextStyle_new(
        style->text_font,
        style->text_size,
        style->colors->text,
        style->text_style,
        EdgeInsets_zero(),
        EdgeInsets_zero()
    ), Position_null(), false);
    button->rect = rect;
    button->style = style;
    button->input = app->input;
    button->hovered = false;
    button->pressed = false;
    button->focused = false;
    button->parent = parent;

    return button;
}

void Button_destroy(Button* button) {
    if (!button) return;
    Text_destroy(button->text);
    ButtonStyle_destroy(button->style);
    safe_free((void**)&button);
}

void Button_render(Button* button, SDL_Renderer* renderer) {

    Text_setColor(button->text, button->style->colors->text);

    Color* border = button->style->colors->border;
    Color* fill = button->style->colors->background;
    SDL_SetRenderDrawColor(renderer, border->r, border->g, border->b, border->a);
    SDL_FRect borderRect = { button->rect.x - 2, button->rect.y - 2, button->rect.w + 4, button->rect.h + 4};
    SDL_RenderFillRect(renderer, &borderRect);

    SDL_SetRenderDrawColor(renderer, fill->r, fill->g, fill->b, fill->a);
    SDL_RenderFillRect(renderer, &button->rect);

    const float textX = button->rect.x + (button->rect.w / 2) - (Text_getSize(button->text).width / 2);
    const float textY = button->rect.y + (button->rect.h / 2) - (Text_getSize(button->text).height / 2);
    Text_setPosition(button->text, textX, textY);
    Text_render(button->text);
}

void Button_update(Button* button) {
    if (!button->focused) {
        Button_focus(button);
    }
}

void Button_unFocus(Button* button) {
    //log_message(LOG_LEVEL_DEBUG, "Button %s unfocused", button->text->text);
    button->focused = false;
    Input_removeOneEventHandler(button->input, SDL_EVENT_MOUSE_MOTION, button);
    Input_removeOneEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_DOWN, button);
    Input_removeOneEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_UP, button);
}

void Button_focus(Button* button) {
    //log_message(LOG_LEVEL_DEBUG, "Button %s focused", button->text->text);
    button->focused = true;
    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_MOTION, Button_checkHover, button);
    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_DOWN, Button_checkPressed, button);
    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_UP, Button_checkPressed, button);
}

void Button_setString(Button* button, const char* str) {
    if (!str || !button) return;
    Text_setString(button->text, str);
}

void Button_setStringf(Button* button, const char* format, ...) {
    if (!format || !button) return;
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    Text_setString(button->text, buffer);
}

void Button_setParent(Button* button, void* parent) {
    if (!button) return;
    button->parent = parent;
}

static void Button_checkHover(Input* input, SDL_Event* evt, void* buttonData) {
    Button* button = buttonData;
    bool isHovering = Input_mouseInRect(input, (SDL_FRect){
        .x = (int)button->rect.x,
        .y = (int)button->rect.y,
        .w = (int)button->rect.w,
        .h = (int)button->rect.h
    });
    if (isHovering && !button->hovered) {
        //log_message(LOG_LEVEL_DEBUG, "Button hovered");
        button->hovered = true;
        if (button->onHover) {
            button->onHover(input, evt, buttonData);
        }
    } else if (!isHovering && button->hovered) {
        button->hovered = false;
        if (button->onHoverEnd) {
            button->onHoverEnd(input, evt, buttonData);
        }
    }
}

static void Button_checkPressed(Input* input, SDL_Event* evt, void* buttonData) {
    Button* button = buttonData;
    bool isHovering = Input_mouseInRect(input, (SDL_FRect){
        .x = (int)button->rect.x,
        .y = (int)button->rect.y,
        .w = (int)button->rect.w,
        .h = (int)button->rect.h
    });
    if (isHovering && evt->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        button->pressed = true;
        if (button->onClick) {
            button->onClick(input, evt, buttonData);
        }
    } else if (isHovering && evt->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        button->pressed = false;
    } else {
        button->pressed = false;
    }
}

void Button_onClick(Button* button, EventHandlerFunc func) {
    button->onClick = func;
}

void Button_onHover(Button* button, EventHandlerFunc func) {
    button->onHover = func;
}

void Button_onHoverEnd(Button* button, EventHandlerFunc func) {
    button->onHoverEnd = func;
}