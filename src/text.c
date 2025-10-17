/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "text.h"

#include "logger.h"
#include "utils.h"

void refreshTexture(Text* self);

Text* Text_new(SDL_Renderer* renderer, TTF_Font* font, const char* str, SDL_Color color) {
    Text* text = calloc(1, sizeof(Text));
    if (!text) {
        error("Failed to allocate memory for Text");
        return NULL;
    }
    text->renderer = renderer;
    text->font = font;
    text->text = Strdup(str);
    text->color = color;
    text->texture = NULL;

    refreshTexture(text);

    return text;
}

void Text_destroy(Text* self) {
    if (!self) return;

    if (self->texture) {
        SDL_DestroyTexture(self->texture);
    }
    safe_free((void**)&(self->text));
    safe_free((void**)&self);
}

void Text_setString(Text* self, const char* str) {
    if (strcmp(self->text, str) == 0) {
        return;
    }

    safe_free((void**)&(self->text));
    self->text = Strdup(str);

    refreshTexture(self);
}

void Text_setColor(Text* self, SDL_Color color) {
    if (memcmp(&(self->color), &color, sizeof(SDL_Color)) == 0) {
        return;
    }

    self->color = color;
    refreshTexture(self);
}

void refreshTexture(Text* self) {
    if (self->texture) {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(self->font, self->text, strlen(self->text), self->color);
    if (!surface) {
        error("Failed to create text surface.");
        return;
    }

    self->texture = SDL_CreateTextureFromSurface(self->renderer, surface);
    if (!self->texture) {
        error("Failed to create text texture.");
        SDL_FreeSurface(surface);
        return;
    }

    SDL_FreeSurface(surface);
}

void Text_render(Text* self, float x, float y) {
    if (!self || !self->texture) return;
    float w, h;
    SDL_GetTextureSize(self->texture, &w, &h);

    SDL_FRect dst = { x, y, w, h };
    if (SDL_RenderCopyF(self->renderer, self->texture, NULL, &dst) != 0) {
        error("Failed to render text texture.");
    }
}
