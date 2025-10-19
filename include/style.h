/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

struct EdgeInsets {
    float top, bottom, left, right;
};

#define EdgeInsets_zero() EdgeInsets_new(0, 0, 0, 0)
#define EdgeInsets_newAll(value) EdgeInsets_new(value, value, value, value)
#define EdgeInsets_newSymmetric(vertical, horizontal) EdgeInsets_new(vertical, vertical, horizontal, horizontal)
EdgeInsets* EdgeInsets_new(float top, float bottom, float left, float right);
void EdgeInsets_destroy(EdgeInsets* insets);

struct TextStyle {
    TTF_Font* font;
    int size;
    Color* color;
    TTF_FontStyleFlags style;
};

TextStyle* TextStyle_new(TTF_Font* font, int size, Color* color, TTF_FontStyleFlags style);
void TextStyle_destroy(TextStyle* style);
TextStyle* TextStyle_default(ResourceManager* resource_manager);
TextStyle* TextStyle_defaultFromTheme(Theme* theme, ResourceManager* resource_manager);

struct FullStyleColors {
    Color* background;
    Color* border;
    Color* text;
};

FullStyleColors* FullStyleColors_new(Color* background, Color* border, Color* text);
void FullStyleColors_destroy(FullStyleColors* colors);

struct ButtonStyle {
    FullStyleColors* colors;
    int border_width;
    TTF_Font* text_font;
    TTF_FontStyleFlags text_style;
    int text_size;
    EdgeInsets* paddings;
};

ButtonStyle* ButtonStyle_new(FullStyleColors* colors, int border_width, TTF_Font* text_font, TTF_FontStyleFlags text_style, int text_size, EdgeInsets* paddings);
void ButtonStyle_destroy(ButtonStyle* style);
ButtonStyle* ButtonStyle_default(ResourceManager* resource_manager);
ButtonStyle* ButtonStyle_defaultFromTheme(Theme* theme, ResourceManager* resource_manager);

struct InputBoxStyle {
    TTF_Font* font;
    int text_size;
    TTF_FontStyleFlags style;

    FullStyleColors* colors;
};

InputBoxStyle* InputBoxStyle_new(TTF_Font* font, int text_size, TTF_FontStyleFlags style, FullStyleColors* colors);
void InputBoxStyle_destroy(InputBoxStyle* style);
InputBoxStyle* InputBoxStyle_default(ResourceManager* resource_manager);
InputBoxStyle* InputBoxStyle_defaultFromTheme(Theme* theme, ResourceManager* resource_manager);

struct Theme {
    Color* background;
    Color* primary;
    Color* secondary;

    TextStyle* title_style;
    TextStyle* body_style;

    ButtonStyle* button_style;
};

Theme* Theme_new(Color* background, Color* primary, Color* secondary, TextStyle* title_style, TextStyle* body_style, ButtonStyle* button_style);
void Theme_destroy(Theme* theme);
Theme* Theme_default(ResourceManager* resource_manager);