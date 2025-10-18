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

static void Button_checkHover(Input* input, SDL_Event* evt, void* buttonData);
static void Button_checkPressed(Input* input, SDL_Event* evt, void* buttonData);

Button* Button_new(const App* app, const char* label, SDL_FRect rect, Color* border_color, Color* fill_color, Color* text_color, TTF_Font* font) {
    Button* button = calloc(1, sizeof(Button));
    if (!button) {
        error("Failed to allocate memory for Button");
        return NULL;
    }
    button->text = Text_new(app->renderer, font, label, Color_toSDLColor(text_color));
    button->rect = rect;
    button->border_color = border_color;
    button->fill_color = fill_color;
    button->text_color = text_color;
    button->input = app->input;
    button->hovered = false;
    button->pressed = false;

    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_MOTION, Button_checkHover, button);
    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_DOWN, Button_checkPressed, button);
    Input_addEventHandler(button->input, SDL_EVENT_MOUSE_BUTTON_UP, Button_checkPressed, button);
    return button;
}

void Button_destroy(Button* button) {
    if (!button) return;
    Text_destroy(button->text);
    safe_free((void**)&button->border_color);
    safe_free((void**)&button->fill_color);
    safe_free((void**)&button);
}

void Button_render(SDL_Renderer* renderer, Button* button) {
    Color* border = button->hovered ? button->fill_color : button->border_color;
    Color* fill = button->pressed ? Color_rgba(0, 0, 0, 0) : button->hovered ? button->border_color : button->fill_color;
    SDL_SetRenderDrawColor(renderer, border->r, border->g, border->b, border->a);
    if (button->pressed) {
        Text_setColor(button->text, Color_toSDLColor(button->fill_color));
        SDL_RenderStroke(renderer, &button->rect, 2.0f);
    } else {
        Text_setColor(button->text, Color_toSDLColor(button->text_color));
        SDL_FRect borderRect = { button->rect.x - 2, button->rect.y - 2, button->rect.w + 4, button->rect.h + 4};
        SDL_RenderFillRect(renderer, &borderRect);
    }

    SDL_SetRenderDrawColor(renderer, fill->r, fill->g, fill->b, fill->a);
    SDL_RenderFillRect(renderer, &button->rect);

    const float textX = button->rect.x + (button->rect.w / 2) - (Text_getSize(button->text).width / 2);
    const float textY = button->rect.y + (button->rect.h / 2) - (Text_getSize(button->text).height / 2);
    Text_render(button->text, textX, textY);
}

void Button_update(Button* button) {

}

static void Button_checkHover(Input* input, SDL_Event* evt, void* buttonData) {
    Button* button = buttonData;
    bool isHovering = Input_mouseInRect(input, (SDL_Rect){
        .x = (int)button->rect.x,
        .y = (int)button->rect.y,
        .w = (int)button->rect.w,
        .h = (int)button->rect.h
    });
    if (isHovering && !button->hovered) {
        log_message(LOG_LEVEL_DEBUG, "Button %s hovered", button->text->text);
        button->hovered = true;
        if (button->onHover) {
            button->onHover(input, evt, buttonData);
        }
    } else if (!isHovering && button->hovered) {
        log_message(LOG_LEVEL_DEBUG, "Button %s unhovered", button->text->text);
        button->hovered = false;
        if (button->onHoverEnd) {
            button->onHoverEnd(input, evt, buttonData);
        }
    }
}

static void Button_checkPressed(Input* input, SDL_Event* evt, void* buttonData) {
    Button* button = buttonData;
    bool isHovering = Input_mouseInRect(input, (SDL_Rect){
        .x = (int)button->rect.x,
        .y = (int)button->rect.y,
        .w = (int)button->rect.w,
        .h = (int)button->rect.h
    });
    if (isHovering && evt->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        log_message(LOG_LEVEL_DEBUG, "Mouse button %s down", button->text->text);
        button->pressed = true;
        if (button->onClick) {
            button->onClick(input, evt, buttonData);
        }
    } else if (isHovering && evt->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        log_message(LOG_LEVEL_DEBUG, "Mouse button %s up", button->text->text);
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