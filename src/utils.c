/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "utils.h"
#include "app.h"
#include "logger.h"

Position* Position_new(const int x, const int y) {
    Position* pos = calloc(1, sizeof(Position));
    if (!pos) {
        error("Failed to allocate memory for Position");
        return NULL;
    }
    pos->x = x;
    pos->y = y;
    return pos;
}

void Position_destroy(Position* pos) {
    if (!pos) return;
    safe_free((void**)&pos);
}

void safe_free(void** ptr) {
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}

int init() {
    Uint32 sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

    if (!SDL_Init(sdlFlags)) {
        error("Unable to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!TTF_Init()) {
        error("Unable to initialize SDL_ttf: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!MIX_Init()) {
        error("Unable to initialize SDL_mixer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

SDL_FRect createRect(const float x, const float y, const float w, const float h) {
    SDL_FRect rect = { 0 };
    rect.w = w;
    rect.h = h;
    rect.x = x - (w / 2);
    rect.y = y - (h / 2);

    return rect;
}

void SDL_RenderStroke(SDL_Renderer* renderer, const SDL_FRect* rect, const float thickness) {
    const SDL_FRect top = { rect->x, rect->y, rect->w, thickness };
    const SDL_FRect bottom = { rect->x, rect->y + rect->h - thickness, rect->w, thickness };
    const SDL_FRect left = { rect->x, rect->y, thickness, rect->h };
    const SDL_FRect right = { rect->x + rect->w - thickness, rect->y, thickness, rect->h };

    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
}

Color* Color_rgb(const int r, const int g, const int b) {
    return Color_rgba(r, g, b, 255);
}

Color* Color_rgba(const int r, const int g, const int b, const int a) {
    Color* color = (Color*)calloc(1, sizeof(Color));
    if (!color) {
        error("Failed to allocate memory for Color");
        return NULL;
    }
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
    return color;
}

Color* Color_hsv(float h, float s, float v) {
    float dR, dG, dB;
    int r, g, b;

    h = fmodf(h, 360.0f);
    float c = v * s;
    float x = c * (1.f - fabsf(fmodf(h / 60.f, 2.f) - 1.f));
    float m = v - c;

    if (h < 60) {
        dR = c; dG = x; dB = 0;
    } else if (h < 120) {
        dR = c; dG = x, dB = 0;
    } else if (h < 180) {
        dR = 0; dG = c; dB = x;
    } else if (h < 240) {
        dR = 0; dG = x; dB = c;
    } else if (h < 300) {
        dR = x; dG = 0; dB = c;
    } else {
        dR = c; dG = 0; dB = x;
    }

    r = (int) roundf((dR + m) * 255.f);
    g = (int) roundf((dG + m) * 255.f);
    b = (int) roundf((dB + m) * 255.f);
    return Color_rgb(r, g, b);
}

void Color_destroy(Color* color) {
    if (!color) return;
    safe_free((void**)&color);
}

SDL_Color Color_toSDLColor(Color* color) {
    return (SDL_Color){ color->r, color->g, color->b, color->a };
}

char* Strdup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1);
    if (!copy) {
        error("Failed to allocate memory for string duplication");
        return NULL;
    }
    for (size_t i = 0; i <= len; i++) {
        copy[i] = str[i];
    }
    copy[len] = '\0';
    return copy;
}

// To remove
#include <dirent.h>
#include <sys/stat.h>


int file_exists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

void list_dir(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) {
        printf("Impossible d’ouvrir le dossier : %s\n", path);
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}