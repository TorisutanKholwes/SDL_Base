/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "button.h"

#include "logger.h"
#include "utils.h"
#include "text.h"
#include "app.h"

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
    button->input = app->input;
    button->hovered = false;
    button->pressed = false;
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
    SDL_SetRenderDrawColor(renderer, button->border_color->r, button->border_color->g, button->border_color->b, button->border_color->a);
    SDL_FRect borderRect = { button->rect.x - 2, button->rect.y - 2, button->rect.w + 4, button->rect.h + 4};
    SDL_RenderFillRectF(renderer, &borderRect);

    SDL_SetRenderDrawColor(renderer, button->fill_color->r, button->fill_color->g, button->fill_color->b, button->fill_color->a);
    SDL_RenderFillRectF(renderer, &button->rect);

    float textX = button->rect.x + (button->rect.w / 2);
    float textY = button->rect.y + (button->rect.h / 2);
    Text_render(button->text, textX, textY);
}

void Button_update(Button* button) {

}

void Button_hover(Input* input, SDL_Event* evt) {

}

void Button_pressed(Input* input, SDL_Event* evt) {

}