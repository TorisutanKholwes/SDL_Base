/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "input_box.h"

#include "app.h"
#include "input.h"
#include "list.h"
#include "logger.h"
#include "map.h"
#include "style.h"
#include "text.h"
#include "utils.h"

static void InputBox_checkKeyDown(Input* input, SDL_Event* event, void* data);
static void InputBox_checkMouseClick(Input* input, SDL_Event* event, void* data);

InputBox *InputBox_new(App *app, SDL_FRect rect, InputBoxStyle *style, void* parent) {
    InputBox *self = calloc(1, sizeof(InputBox));
    if (!self) {
        error("Failed to allocate memory for InputBox");
        return NULL;
    }
    self->rect = rect;
    self->style = style;
    self->app = app;
    self->input = app->input;
    self->text = Text_new(app->renderer, "", TextStyle_new(
                              style->font,
                              style->text_size,
                              style->colors->text,
                              style->style,
                              EdgeInsets_zero(),
                              EdgeInsets_zero()
                          ), Position_null(), false);
    self->focused = false;
    self->selected = false;
    self->parent = parent;
    return self;
}

void InputBox_destroy(InputBox *self) {
    if (!self) return;
    Text_destroy(self->text);
    InputBoxStyle_destroy(self->style);
    safe_free((void **) &self);
}

void InputBox_render(InputBox *self, SDL_Renderer *renderer) {

    Text_setColor(self->text, self->style->colors->text);

    Color *border = self->style->colors->border;
    Color *fill = self->style->colors->background;
    SDL_SetRenderDrawColor(renderer, border->r, border->g, border->b, border->a);

    SDL_FRect borderRect = {self->rect.x - 2, self->rect.y - 2, self->rect.w + 4, self->rect.h + 4};
    SDL_RenderFillRect(renderer, &borderRect);

    SDL_SetRenderDrawColor(renderer, fill->r, fill->g, fill->b, fill->a);
    SDL_RenderFillRect(renderer, &self->rect);

    const float textX = self->rect.x + 5; // Padding of 5
    const float textY = self->rect.y + (self->rect.h / 2) - (Text_getSize(self->text).height / 2);
    Text_setPosition(self->text, textX, textY);
    if (!String_isNullOrEmpty(self->text->text)) {
        Text_render(self->text);
    }
}

void InputBox_update(InputBox *self) {
    if (!self->focused) {
        InputBox_focus(self);
    }
}

void InputBox_setParent(InputBox *self, void *parent) {
    self->parent = parent;
}

void InputBox_focus(InputBox *self) {
    self->focused = true;
    Input_addEventHandler(self->input, SDL_EVENT_TEXT_INPUT, InputBox_checkKeyDown, self);
    Input_addEventHandler(self->input, SDL_EVENT_KEY_DOWN, InputBox_checkKeyDown, self);
    Input_addEventHandler(self->input, SDL_EVENT_MOUSE_BUTTON_DOWN, InputBox_checkMouseClick, self);
}

void InputBox_unFocus(InputBox *self) {
    self->focused = false;
    Input_removeOneEventHandler(self->input, SDL_EVENT_TEXT_INPUT, self);
    Input_removeOneEventHandler(self->input, SDL_EVENT_KEY_DOWN, self);
    Input_removeOneEventHandler(self->input, SDL_EVENT_MOUSE_BUTTON_DOWN, self);
    if (self->selected) {
        SDL_StopTextInput(self->app->window);
    }
}

void InputBox_setString(InputBox *self, const char *str) {
    Text_setString(self->text, str);
}

void InputBox_setStringf(InputBox *self, const char *format, ...) {
    if (!format || !self) return;
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    Text_setString(self->text, buffer);
}

char* InputBox_getString(InputBox* input_box) {
    if (!input_box) return NULL;
    return input_box->text->text;
}

static void InputBox_checkMouseClick(Input* input, SDL_Event* event, void* data) {
    if (!data || !event || !input) return;
    InputBox* self = data;
    if (event->button.button != SDL_BUTTON_LEFT) {
        return;
    }
    if (Input_mouseInRect(input, self->rect)) {
        log_message(LOG_LEVEL_DEBUG, "Input now selected");
        self->selected = true;
        SDL_StartTextInput(self->app->window);
    } else if (self->selected) {
        log_message(LOG_LEVEL_DEBUG, "Input now unselected");
        self->selected = false;
        SDL_StopTextInput(self->app->window);
    }
}

static void InputBox_checkKeyDown(Input* input, SDL_Event* event, void* data) {
    if (!data || !event || !input) return;
    InputBox* self = data;
    if (!self->selected) {
        return;
    }
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_BACKSPACE:
                    char* currentText = self->text->text;
                    size_t len = strlen(currentText);
                    if (len > 0) {
                        currentText[len - 1] = '\0';
                        Text_setString(self->text, currentText);
                    }
                    break;
                default:
                    break;
            }
            break;
        case SDL_EVENT_TEXT_INPUT:
            Text_setStringf(self->text, "%s%s", self->text->text, event->text.text);
            break;
        default:
            log_message(LOG_LEVEL_WARN, "Event type %d not recognized", event->type);
            break;
    }
}
