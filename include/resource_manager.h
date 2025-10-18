/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#pragma once

#include "Settings.h"

#define ASSETS_PATH "../assets/"

#define TEXTURE_PATH ASSETS_PATH "textures/"
#define FONT_PATH    ASSETS_PATH "fonts/"
#define SOUND_PATH   ASSETS_PATH "sounds/"

#define DEFAULT_FONT "Cinzel-Regular.ttf"

struct ResourceManager {
    SDL_Renderer* renderer;
    MIX_Mixer* mixer;
    Map* texturesCache;
    Map* fontsCache;
    Map* soundsCache;
};

ResourceManager* ResourceManager_create(SDL_Renderer* renderer, MIX_Mixer* mixer);
void ResourceManager_destroy(ResourceManager* self);
SDL_Texture* ResourceManager_getTexture(ResourceManager* self, const char* filename);
TTF_Font* ResourceManager_getFont(ResourceManager* self, const char* filename, int size);
MIX_Audio* ResourceManager_getSound(ResourceManager* self, const char* filename);

INLINE TTF_Font* ResourceManager_getDefaultFont(ResourceManager* self, int size) {
    return ResourceManager_getFont(self, DEFAULT_FONT, size);
}