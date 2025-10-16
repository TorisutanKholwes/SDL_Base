/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

#include "Settings.h"

typedef struct MapNode MapNode;
struct MapNode {
    void* key;
    void* value;
    MapNode* next;
    MapNode* prev;
};

typedef struct {
    MapNode* root;
    size_t size;
} Map;

typedef struct {
    MapNode* root;
    MapNode* current;
} MapIterator;

Map* Map_create();
void Map_destroy(Map* map);
void Map_clear(Map* map);
void Map_put(Map* map, void* key, void* value);
void* Map_get(Map* map, void* key);
bool Map_containsKey(Map* map, void* key);
bool Map_containsValue(Map* map, void* key);
void Map_remove(Map* map, void* key);
size_t Map_size(Map* map);
bool Map_isEmpty(Map* map);
void Map_toString(Map* map, const char* format, void* (*formatKeyFunc)(void* key), void* (*formatValueFunc)(void* value));

MapIterator* Map_iterator(Map* map);
void MapIterator_destroy(MapIterator* iterator);
bool MapIterator_hasNext(MapIterator* iterator);
void MapIterator_next(MapIterator* iterator);
void* MapIterator_key(MapIterator* iterator);
void* MapIterator_value(MapIterator* iterator);

